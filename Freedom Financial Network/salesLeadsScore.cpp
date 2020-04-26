struct comparator {
  bool operator() (const tuple<float,int,string>& lhs, const tuple<float,int,string>& rhs) const{
    if (get<0>(lhs) == get<0>(rhs)) {
        if (get<1>(lhs) == get<1>(rhs)) {
            return get<2>(lhs) > get<2>(rhs); 
        }
        else {
            return get<1>(lhs) < get<1>(rhs); 
        }
    } else {
        return get<0>(lhs) < get<0>(rhs);
    }
  }
};

std::vector<std::string> salesLeadsScore(std::vector<std::string> names, std::vector<int> time, std::vector<int> netValue, std::vector<bool> isOnVacation) {
    multiset<tuple<float,int,string>,comparator> leads;
    vector<string> output;
    for(int i = 0 ; i < names.size(); i++){
        if(!isOnVacation[i]){
            float score = netValue[i] * time[i] / 365.0;
            leads.insert(make_tuple(score, time[i],names[i]));
        }
    }

    for(auto x = leads.rbegin(); x != leads.rend(); ++x){
        output.insert(output.end(),1,get<2>(*x));
    }
    return output;
}

