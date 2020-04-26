int bnew_r(int a, int b, int d){
    double n = ((b * 100.0 + a * d) / 100);
    if((n - floor(n)) > 0.5){
        return ceil(n);
    } else return floor(n);
}
int bnew_a(int a, int b, int d){
    double n = ((b * 100.0 + a * d) / 100);
    return round(n);
}

bool lessthen(pair<int,int>& a, pair<int, int>& b){
    if (a.second < b.second) {
        return true;
    } else if(a.second == b.second){
        return a.first < b.first;
    } else {
        return false;
    }
}
bool lesstheneq(pair<int,int>& a, pair<int, int>& b){
    if (a.second < b.second) {
        return true;
    } else if(a.second == b.second){
        return a.first <= b.first;
    } else {
        return false;
    }
}

void initHistory(vector<pair<int,tuple<int,int,int>>>& history, vector<string>& historyStrings, pair<int,int> StartDate, pair<int,int> EndDate){
    for(int i = 0; i < historyStrings.size();){
        string& s = historyStrings[i++];
        int index = s.find(' ');
        int amount = stoi(s.substr(1,index));
        int d,m,y;
        m = stoi(s.substr(s.length() - 10,2));
        d = stoi(s.substr(s.length() - 7,2));
        y = stoi(s.substr(s.length() - 4,4));
        pair<int,int> temp = make_pair(m,y);
        while(lessthen(StartDate,temp)){
            if(StartDate == EndDate){
                return;
            }
            history.insert(history.end(),1,make_pair(0,make_tuple(16,StartDate.first,StartDate.second)));
            StartDate.first++;
            if(StartDate.first > 12){
                StartDate.second++;
                StartDate.first = 1;
            }
        }
        history.insert(history.end(),1,make_pair(amount,make_tuple(d,m,y)));
        StartDate.first++;
        if(StartDate.first > 12){
            StartDate.second++;
            StartDate.first = 1;
        }
    }
    while(lesstheneq(StartDate,EndDate)){
        history.insert(history.end(),1,make_pair(0,make_tuple(16,StartDate.first,StartDate.second)));
        StartDate.first++;
        if(StartDate.first > 12){
            StartDate.second++;
            StartDate.first = 1;
        }
    }
}

bool isLate(list<pair<int,tuple<int,int,int>>>& historybuffer){
    for(auto& x : historybuffer){
        if(get<0>(x.second) <= 15){
            return false;
        }
    }
    return true;
}

bool didNotPay(list<pair<int,tuple<int,int,int>>> historybuffer){
    auto& temp = historybuffer.back();
    if(temp.first != 0){
        return false;
    }
    historybuffer.pop_back();
    temp = historybuffer.back();
    if(temp.first != 0){
        return false;
    }
    return true;
}

bool didPayTwice(list<pair<int,tuple<int,int,int>>>& historybuffer, int& b){
    for(auto& x: historybuffer){
        if(x.first < 2 * b){
            return false;
        }
    }
    return true;
}

string analyze(list<pair<int,tuple<int,int,int>>>& historybuffer,int& a, int& b, int& sum){
    if(historybuffer.size() == 1 || historybuffer.size() == 2){
        return "Leave as it is, " + to_string(b) + ".";
    } else {
        if(historybuffer.size() == 4){
            sum -= historybuffer.front().first;
            historybuffer.pop_front();
        }
        if(sum < 3*b || isLate(historybuffer) || didNotPay(historybuffer)){
            b = bnew_a(a,b,1);
            return "Add one year, " + to_string(b) + ".";
        } else if(didPayTwice(historybuffer,b)){
            b = bnew_r(a,b,-1);
            return "Remove one year, " + to_string(b) + ".";
        }
        return "Leave as it is, " + to_string(b) + ".";
    }
}

std::vector<std::string> creditPayments(int a, int b, std::string startDate, std::string endDate, std::vector<std::string> historyStrings) {
    vector<string> output;
    string startMonth = startDate.substr(0,2);
    string startYear = startDate.substr(3);
    pair<int,int> StartDate = make_pair(stoi(startMonth),stoi(startYear)); // month, year
    string endMonth = endDate.substr(0,2);
    string endYear = endDate.substr(3);
    pair<int,int> EndDate = make_pair(stoi(endMonth),stoi(endYear)); // month, year
    pair<int,int> currentDate = StartDate; // month, year
    vector<pair<int,tuple<int,int,int>>> history;
    list<pair<int,tuple<int,int,int>>> historybuffer;
    initHistory(history, historyStrings, StartDate, EndDate);
    int sum = 0;
    for(auto& p : history){
        historybuffer.push_back(p);
        sum += p.first;
        output.push_back(analyze(historybuffer, a, b, sum));
    }
    return output;
}
