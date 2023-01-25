/*
Polly Poliwag
Program simulates simple pokemon battles!
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Set.h"
#include "HashMap.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

/* Makes sure that getline returns a nonempty line */
bool getLineNotWS(istream& in, string& inpString) {
	if (getline(in, inpString)) {
		if (inpString.find_first_not_of(" \t") == std::string::npos) {
			getline(in, inpString);
		}
		return true;
	}
	else return false;
}

int main(int argc, char * argv[])
{
	VS_MEM_CHECK    // enables memory leak check
	
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	string line, input, data1, data2, pokemon1, move1, pokemon2, move2;
	HashMap<string, string> myPokemon;
	HashMap<string, string> myMoves;
	HashMap<string, Set<string>> myEffectivities;
	HashMap<string, Set<string>> myIneffectivities;
	
	try {
		while (getLineNotWS(in, line)) {
			istringstream iss(line);
			iss >> input;
			if (input == "Set:") { // make and output set
				out << line << endl;
				Set<string> mySet;
				while (iss >> data1) mySet.insert(data1);
				out << "  [" << mySet << "]" << endl << endl;
			}
			else if (input == "Pokemon:") { // put pokemon in the myPokemon hashmap
				out << line << endl;
				iss >> data1 >> data2;
				myPokemon[data1] = data2;
			}
			else if (input == "Move:") { // put moves in the myMoves hashmap
				out << line << endl;
				iss >> data1 >> data2;
				myMoves[data1] = data2;
			}
			else if (input == "Effective:") { // put a set of effectivities in the myEffectivities hashmap
				out << line << endl;
				iss >> data1;
				Set<string> mySet;
				while (iss >> data2) mySet.insert(data2);
				myEffectivities[data1] = mySet;
			}
			else if (input == "Ineffective:") { // put a set of ineffectivities in the myIneffectivities hashmap
				out << line << endl;
				iss >> data1;
				Set<string> mySet;
				while (iss >> data2) mySet.insert(data2);
				myIneffectivities[data1] = mySet;
			}
			else if (input == "Pokemon") { // outputs the myPokemon hashmap
				out << endl << input << ": " << myPokemon.size() << "/" << DEFAULT_MAP_HASH_TABLE_SIZE << endl;
				out << myPokemon;
			}
			else if (input == "Moves") { // outputs the myMoves hashmap
				out << endl << input << ": " << myMoves.size() << "/" << DEFAULT_MAP_HASH_TABLE_SIZE << endl;
				out << myMoves;
			}
			else if (input == "Effectivities") { // outputs the myEffectivities hashmap
				out << endl << input << ": " << myEffectivities.size() << "/" << DEFAULT_MAP_HASH_TABLE_SIZE << endl;
				out << myEffectivities;
			}
			else if (input == "Ineffectivities") { // outputs the myIneffectivities hashmap
				out << endl << input << ": " << myIneffectivities.size() << "/" << DEFAULT_MAP_HASH_TABLE_SIZE << endl;
				out << myIneffectivities;
			}
			else if (input == "Battle:") { // simulates the battle between pokemon and names a winner
				out << endl << line << endl;
				iss >> pokemon1 >> move1 >> pokemon2 >> move2;
				int damage1To2 = (myEffectivities[myMoves[move1]].count(myPokemon[pokemon2]) - myIneffectivities[myMoves[move1]].count(myPokemon[pokemon2]));
				int damage2To1 = (myEffectivities[myMoves[move2]].count(myPokemon[pokemon1]) - myIneffectivities[myMoves[move2]].count(myPokemon[pokemon1]));
				out << "  " << pokemon1 << " (" << move1 << ") vs " << pokemon2 << " (" << move2 << ")" << endl;
				out << "  " << pokemon1 << " is a " << myPokemon[pokemon1] << " type Pokemon." << endl;
				out << "  " << pokemon2 << " is a " << myPokemon[pokemon2] << " type Pokemon." << endl;
				out << "  " << move1 << " is a " << myMoves[move1] << " type move." << endl;
				out << "  " << move2 << " is a " << myMoves[move2] << " type move." << endl;
				if (myEffectivities[myMoves[move1]].size() == 0) {
					out << "  " << move1 << " is not effective against any Pokemon" << endl;
				}
				else {
					out << "  " << move1 << " is super effective against [" << myEffectivities[myMoves[move1]] << "] type Pokemon." << endl;
				}
				if (myIneffectivities[myMoves[move1]].size() == 0) {
					out << "  " << move1 << " is not ineffective against any Pokemon." << endl;
				}
				else {
					out << "  " << move1 << " is ineffective against [" << myIneffectivities[myMoves[move1]] << "] type Pokemon." << endl;
				}
				if (damage1To2 == -1) out << "  " << pokemon1 << "'s " << move1 << " is ineffective against " << pokemon2 << endl;
				else if (damage1To2 == 0) out << "  " << pokemon1 << "'s " << move1 << " is effective against " << pokemon2 << endl;
				else if (damage1To2 == 1) out << "  " << pokemon1 << "'s " << move1 << " is super effective against " << pokemon2 << endl;
				if (myEffectivities[myMoves[move2]].size() == 0) {
					out << "  " << move2 << " is not effective against any Pokemon" << endl;
				}
				else {
					out << "  " << move2 << " is super effective against [" << myEffectivities[myMoves[move2]] << "] type Pokemon." << endl;
				}
				if (myIneffectivities[myMoves[move2]].size() == 0) {
					out << "  " << move2 << " is not ineffective against any Pokemon." << endl;
				}
				else {
					out << "  " << move2 << " is ineffective against [" << myIneffectivities[myMoves[move2]] << "] type Pokemon." << endl;
				}
				if (damage2To1 == -1) out << "  " << pokemon2 << "'s " << move2 << " is ineffective against " << pokemon1 << endl;
				else if (damage2To1 == 0) out << "  " << pokemon2 << "'s " << move2 << " is effective against " << pokemon1 << endl;
				else if (damage2To1 == 1) out << "  " << pokemon2 << "'s " << move2 << " is super effective against " << pokemon1 << endl;
				if ((damage1To2 - damage2To1) > 0) out << "  In the battle between " << pokemon1 << " and " << pokemon2 << ", " << pokemon1 << " wins!" << endl;
				else if ((damage1To2 - damage2To1) < 0) out << "  In the battle between " << pokemon1 << " and " << pokemon2 << ", " << pokemon2 << " wins!" << endl;
				else out << "  The battle between " << pokemon1 << " and " << pokemon2 << " is a tie." << endl;
			}
		}
	}
	catch (exception& e) { out << e.what(); }
	
	return 0;
}