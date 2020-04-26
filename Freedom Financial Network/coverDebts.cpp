double coverDebts(int s, std::vector<int> debts, std::vector<int> interests) {
    double amount_spend = 0;
    vector<pair<double,double>> interest_debt;
    for (int i = 0; i < debts.size(); i++) {
        interest_debt.insert(interest_debt.end(),1,make_pair(interests[i]/100.0, debts[i]));
    }
    sort(interest_debt.begin(),interest_debt.end(),[] (auto item1, auto item2) {
        return get<0>(item1) > get<0>(item2);
    });
    bool isDebtPaid = false;
    while(!isDebtPaid){
        double max = s * 0.1;
        isDebtPaid = true;
        for(int i = 0; i < interest_debt.size() && max != 0; i++){
            if(interest_debt[i].second != 0){
                isDebtPaid = false;
            }
            if(interest_debt[i].second <= max){
                amount_spend += interest_debt[i].second;
                max -= interest_debt[i].second;
                interest_debt[i].second = 0;
            } else {
                amount_spend += max;
                interest_debt[i].second -= max;
                max = 0;
            }
        }
        for(int i = 0; i < interest_debt.size(); i++){
            interest_debt[i].second += interest_debt[i].second * interest_debt[i].first;
        }
    }
    return amount_spend;
}

