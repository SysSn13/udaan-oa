#include <bits/stdc++.h>
using namespace std;

struct Event{
	int id;
	string date;
	int start,dur;
	vector<int> users;
	Event(int id,string date,int start,int dur):id(id),date(date),start(start),dur(dur){}
};


int currId=0;
struct User{
	int id;
	string name;
	unordered_map<string,vector<bool>> cal;
	unordered_map<string,vector<int>> events;
	User(int id,string name):id(id),name(name){
	}

};

vector<User> users;
unordered_map<string,int> userIdMap;


unordered_map<string,vector<Event>> eventMap;

vector<string> parseUsers(string &s){
	stringstream ss(s);
	string userid;
	vector<string> res;
	while(getline(ss,userid,' ')){
		res.push_back(userid);
	}
	return res;
}

void addUser(string &s){
	auto v = parseUsers(s);
	for(auto ele:v){
		if(!userIdMap.count(ele)){
			userIdMap[ele] = currId;
			users.push_back(User(currId++,ele));
		}
		else{
			cout<<"failure\n";
			return;
		}
	}
	cout<<"success\n";
}


bool isNum(string &s){
	for(auto ele:s){
		if(!(ele>='0' && ele<='9')){
			return false;
		}
	}
	return true;
}
bool checkDate(string &s){
	stringstream ss(s);
	string w;
	vector<string> v;
  	while(getline(ss,w,'-')){
		if(!isNum(w)){
			return false;
		}
		v.push_back(w);
	}

	if(v.size()!=3){
		return false;
	}
	int y = stoi(v[0]);
	int m = stoi(v[1]);
	int d = stoi(v[2]);
	if(!(m>=1 && m<=12)){
		return false;
	}
  	if(!(d>=1 && d<=31)){
		return false;
	}
	return true;
}

bool avail(vector<string> &v,string &date,int start,int dur){
	vector<int> ids;
	for(auto ele:v){
		ids.push_back(userIdMap[ele]);
	}
	for(int i=start;i<start+dur;i++){
		for(auto id:ids){
			if(users[id].cal.count(date) && users[id].cal[date][i])
				return false;
		}
	}
	return true;
}

void mark(vector<string> &v,string &date,int start,int dur,int eventId){
	vector<int> ids;
	for(auto ele:v){
		ids.push_back(userIdMap[ele]);
	}


	for(auto id:ids){
		eventMap[date][eventId].users.push_back(id);
		if(!users[id].cal.count(date)){
			users[id].cal[date] = vector<bool>(1460,false);
		}
		users[id].events[date].push_back(eventId);
	}

	for(int i=start;i<start+dur;i++){
		for(auto id:ids){
			users[id].cal[date][i]=true;
		}
	}

}

void createEvent(string &s){
	vector<string> v;
	stringstream ss(s);
	string w;
	while(getline(ss,w,' ')){
		v.push_back(w);
	}
	if((int)v.size()<4 || !checkDate(v[0]) || !isNum(v[1]) || !isNum(v[2]) || !isNum(v[3])){
		cout<<"failure\n";
		return;
	}

	int start = stoi(v[1]);
	int dur = stoi(v[2]);
	int n = stoi(v[3]);
	if(start<0 || start>=1440 || dur<0 || start+dur>=1440){
		cout<<"failure\n";
		return;
	}
	vector<string> u;
	for(int i=4;i<(int)v.size();i++){
		u.push_back(v[i]);
	}
	if(!avail(u,v[0],start,dur)){
		cout<<"failure\n";
		return ;
	}

	eventMap[v[0]].push_back(Event(eventMap[v[0]].size(),v[0],start,dur));
	mark(u,v[0],start,dur,eventMap[v[0]].size()-1);
	cout<<"success\n";
}


void printEvent(Event &e){
	cout<<e.start<<"-"<<e.start+e.dur<<" ";
	for(auto id:e.users){
		cout<<users[id].name<<" ";
	}
	cout<<endl;
}

void showEvents(string &s){
	vector<string> v;
	string w;
	stringstream ss(s);
	while(getline(ss,w,' ')){
		v.push_back(w);
	}
	if(v.size()!=2 || !checkDate(v[0]) || !userIdMap.count(v[1])){
		cout<<"failure\n";
		return;
	}
	string date = v[0];
	int id = userIdMap[v[1]];
	if(users[id].events[date].empty()){
		cout<<"none\n";
		return;
	}

	for(auto ele:users[id].events[date]){
		auto e=  eventMap[date][ele];
		printEvent(e);
	}
}

void suggest(string &date,vector<int> &ids,int start,int end,int dur){
	for(auto id:ids){
		if(!users[id].cal.count(date)){
			users[id].cal[date] = vector<bool>(1440,false);	
		}
	}

	int last = start;
	for(int i=start;i<min(1440,end);i++){

		for(auto id:ids){

			if(users[id].cal[date][i]){
				last = i+1;
			}
		}
		if(i-last+1==dur){
			cout<<last<<endl;
			return;
		}
	}

	cout<<"none\n";
	return;
}


void suggestSlot(string &s){
	vector<string> v;
	string w;
	stringstream ss(s);
	while(getline(ss,w,' ')){
		v.push_back(w);
	}
	if(v.size()<5 || !checkDate(v[0])){
		cout<<"failure\n";
		return ;
	}
	vector<int> ids;
	for(int i=5;i<v.size();i++){
		if(!userIdMap.count(v[i])){
			cout<<"failure\n";
			return;
		}
		ids.push_back(userIdMap[v[i]]);
	}

	string date = v[0];
	int start = stoi(v[1]);
	int end = stoi(v[2]);
	int dur = stoi(v[3]);
	suggest(date,ids,start,end,dur);
}
signed main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		string t,s;
		cin>>t;
		getline(cin,s);
		s= s.substr(1);
		if(t=="add-user"){
			addUser(s);
		}
		else if(t=="create-event"){
			createEvent(s);
		}
		else if(t=="show-events"){
			showEvents(s);
		}
		else if(t=="suggest-slot"){
			suggestSlot(s);
		}
		else{
			cout<<"failure\n";
		}
	}
}
