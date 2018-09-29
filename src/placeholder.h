class placeholder {
public:
    placeholder() = default;
    placeholder(const placeholder &) = default;
    ~placeholder() = default;
public:
    set_var(const string &name,const string &val);
    set_op(const string &name,const function<string&(string&)> &op);
    string &replace(string &str);
private:
    map<string,string> vars;
    map<string,function<string&(string&)>> ops;
};
