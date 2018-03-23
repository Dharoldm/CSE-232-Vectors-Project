#include "proj07_functions.h"

vector<string> split(const string &s, char delim){
	istringstream ss(s);
	string item;
	vector<string> v;
	while (getline(ss, item, delim)) {
	    v.push_back(item);
	}
	return v;
}


void read_data(map<vector<double>, string> &m, unsigned int feature_count, ifstream &inf){

	string line;
	vector<string> raw_vector;
	string unsplit_string;
	string item;
	while(getline(inf, line)){
		stringstream ss(line);
		unsplit_string = ss.str();
		raw_vector = split(unsplit_string, ',');
		vector<double> vector(feature_count);
		for(int i=0;i<feature_count;i++){
			vector[i] = stod(raw_vector[i]);
		}
		item = raw_vector[feature_count];
		m[vector] = item;
	}
	
}

string pair_to_string(const pair<vector<double>, string> &p){
	
	ostringstream ss;
	vector<double> vector = p.first;
	for(int i=0;i<vector.size();i++){
	    ss.precision(3);
		ss << fixed << p.first[i] << " ";
		
	}
	ss << p.second;
	string string = ss.str();
	return ss.str();
	
}

void print_map(const map<vector<double>, string> &m, ostream &out){
	
	for(auto& pair: m){
		out << pair_to_string(pair) << endl;;
		
	}
	
}

double distance(const vector<double> &v1, const vector<double> &v2, unsigned int feature_count){
	double distance;
	for(int i=0;i<feature_count;i++){
		distance+=((v1[i]-v2[i])*(v1[i]-v2[i]));
	}
	distance = sqrt(distance);
	return distance;
}

map<vector<double>, string> k_neighbors(const map<vector<double>, string> &m, const vector<double> &test, int k){
	double distance_from_test;
	double highest_k_distance = 10;
	bool change_highest_k_distance= false;
	int index_to_remove;
	int larger_distance;
	vector<double> key_to_remove;
	map<vector<double>, string> k_neighbors;
	for(auto& pair:m){
		distance_from_test = distance(pair.first, test, test.size());
		if(distance_from_test < highest_k_distance && !(test==pair.first)){
			if (k_neighbors.size()==k){
				larger_distance = distance_from_test;
				for(auto& pair_k:k_neighbors){
					if (larger_distance < distance(pair_k.first,test,test.size())){ //finds the index of the largest item in k_neighbors
						larger_distance = distance(pair_k.first,test,test.size());
						key_to_remove = pair_k.first; //gives the key of the largest distance currently in the map
						change_highest_k_distance == true;
					}
				}
				if( change_highest_k_distance==true){
    				k_neighbors[pair.first] = pair.second;
    				k_neighbors.erase(key_to_remove);
    				highest_k_distance = distance_from_test;
    				change_highest_k_distance == false;
				}
			}
			else if(!(test==pair.first)){
				k_neighbors[pair.first] = pair.second;
			}
		}
	}
    k_neighbors.erase (test); 
    cout << k_neighbors.size() << endl;
	return k_neighbors;
}

double test_one(const map<vector<double>, string> &m, pair<vector<double>, string> test, int k){
	int total=0;
	int correct=0;
	double percent =0.0;
	map<vector<double>, string> neighbors = k_neighbors(m, test.first, k);
	for(auto& element:neighbors){
		if (element.second == test.second){
			correct+=1;
		}
		total+=1;
	}
	percent = correct/total;
	return percent;
}