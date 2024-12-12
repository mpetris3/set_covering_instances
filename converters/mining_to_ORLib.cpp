int main(int argc, char const* argv[]) {

	string path_to_original_instance = "";
	//name of the instance without extension
	string name = "webdocs"; 
	string instance = path_to_original_instance + name + ".dat";
	cout << "\n\nDATASET: " << instance << "\n";

	ifstream stream;
	stream.open(instance.c_str());

	if (!stream.is_open()) {
		cout << "Error opening the file" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	char delimiter = ' ';
	int count_instances = 0;
	vector<vector<int>> subsets;
	unordered_map<int, vector<int>> elements;
	int max_item = -1;
	int min_item = ::OMEGA;
	int sub = 1;
	while (getline(stream, line)) {

		//cout << line << endl;

		stringstream ss(line);
		string token;
		int count_attributes = 0;
		vector<int> subset;
		while (getline(ss, token, delimiter)) {
			int item = stoi(token);
			subset.push_back(item);
			max_item = max(max_item, item);
			min_item = min(min_item, item);
			unordered_map<int, vector<int>>::iterator finder = elements.find(item);
			if (finder == elements.end()) {
				vector<int> aux = { sub };
				elements.insert(make_pair(item, aux));
			}
			else {
				finder->second.push_back(sub);
			}
		}
		subsets.push_back(subset);
		sub++;
	}

	vector<int> elements_found;
	for (const auto& el : elements) {
		elements_found.push_back(el.first);
	}

	ofstream myfile;
	myfile.open(name + ".txt");
	myfile << elements_found.size() << " " << subsets.size() << "\n";
	for (int i = 0; i < subsets.size(); i++) {
		myfile << 1 << " ";
	}
	myfile << "\n";
	for (int j = min_item; j < max_item + 1; j++) {
		//cout << j << endl;
		unordered_map<int, vector<int>>::iterator finder = elements.find(j);
		if (finder != elements.end()) {
			myfile << finder->second.size() << "\n";
			for (int i = 0; i < finder->second.size(); i++) {
				myfile << finder->second.at(i) << " ";
			}
			myfile << "\n";
		}
	}
	myfile.close();

	return 0;
}
