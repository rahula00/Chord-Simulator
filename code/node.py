class Node:
	def __init__(self, id):
		self.id = id
		self.fingerTable = {}
		self.localKeys = {}

	def join(self, node);
		if node == NULL:
			#
		else:
			#add node to network
			#migrate keys

	def find(uint8_t key);
		# implement DHT lookup
		#upon join, the updated finger table should be printed to the screen
		#upon join, print the keys that are migrated

	def insert(uint8_t key, uint8_t value);
		#implement DHT key insertion
		#node needs to query the key from the Chord network. Querying keys are not maintained locally
		#upon find, the sequence of nodes that the node talks to should be printed to the screen too

	
	def remove(uint8_t key);
		#TODO: implement DHT key deletion


	#OPTIONAL TODO (20% extra): implement node leaving
	#not sure if param is supposed to be id
	#locate the node, move keys maintained in the node to another node
	def leave(uint8_t id);