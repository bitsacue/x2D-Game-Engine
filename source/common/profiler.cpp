//       ____  ____     ____                        _____             _            
// __  _|___ \|  _ \   / ___| __ _ _ __ ___   ___  | ____|_ __   __ _(_)_ __   ___ 
// \ \/ / __) | | | | | |  _ / _  |  _   _ \ / _ \ |  _| |  _ \ / _  | |  _ \ / _ \
//  >  < / __/| |_| | | |_| | (_| | | | | | |  __/ | |___| | | | (_| | | | | |  __/
// /_/\_\_____|____/   \____|\__ _|_| |_| |_|\___| |_____|_| |_|\__, |_|_| |_|\___|
//                                                              |___/     
//				Originally written by Marcus Loo Vergara (aka. Bitsauce)
//									2011-2014 (C)

#include <x2d/engine.h>

#define NUM_SAMPLES 10

XProfiler::XProfiler() :
	m_root(new Node(0)),
	m_samples(0)
{
	m_currentNode = m_root;
}

XProfiler::~XProfiler()
{
	recursiveDelete(m_root);
}

void XProfiler::recursiveDelete(Node *node)
{
	for(map<asIScriptFunction*, Node*>::iterator itr = node->children.begin(); itr != node->children.end(); ++itr)
	{
		recursiveDelete(itr->second);
	}
	delete node;
}

void XProfiler::push(asIScriptContext *ctx)
{
	if(ctx)
	{
		// Get function
		asIScriptFunction *func = ctx->GetFunction();
		if(func)
		{
			Node *node = 0;
			if(m_currentNode->children.find(func) == m_currentNode->children.end())
			{
				// Create node if it doesn't exist
				node = new Node(func);
				node->parent = m_currentNode;
				m_currentNode->children[func] = node;
			}
			else
			{
				// Get node
				node = m_currentNode->children[func];
			}

			// Store time and set node
			m_currentNode = node;
			m_currentNode->currentTime = chrono::high_resolution_clock::now();
		}
	}
}

void XProfiler::pop()
{
	if(m_currentNode)
	{
		m_currentNode->durrations.push_back(chrono::high_resolution_clock::now() - m_currentNode->currentTime);
		m_currentNode = m_currentNode->parent;
		if(m_currentNode == m_root && ++m_samples >= 3)
		{
			for(map<asIScriptFunction*, Node*>::iterator itr = m_root->children.begin(); itr != m_root->children.end(); ++itr)
			{
				sendStats(itr->second);
			}
			m_samples = 0;
		}
	}
	else
	{
		LOG("XProfiler::pop() - No current node");
	}
}

void XProfiler::sendStats(Node *node)
{
	// Calculate stuffs
	int total = 0, ave = 0, max = INT_MIN, min = INT_MAX;

	if(!node->durrations.empty())
	{
		for(chrono::high_resolution_clock::duration durr : node->durrations)
		{
			int time = chrono::duration<float, milli>(durr).count();
			if(time < min) min = time;
			if(time > max) max = time;
			total += time;
		}

		ave = total/node->durrations.size();
		node->durrations.clear();
	}

	char *msg = new char[511];
	sprintf_s(msg, 511, "%s;%i ms;%i ms;%i ms", node->function->GetDeclaration(), max, min, ave);
	m_debugger->sendPacket(XD_PUSH_NODE_PACKET, msg);

	// Recursive call to children
	for(map<asIScriptFunction*, Node*>::iterator itr = node->children.begin(); itr != node->children.end(); ++itr)
	{
		sendStats(itr->second);
	}
	
	// Pop stack level
	m_debugger->sendPacket(XD_POP_NODE_PACKET);
}