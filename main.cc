#include <bits/stdc++.h>

#include "snake.h"
#include "graphic.h" 

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

 
using namespace std;
   
typedef pair<int,int> pll;

template<class t1,class t2> 
pair<t1,t2> operator+(pair<t1,t2> &a, pair<t1,t2> &b){
	return {a.first+b.first,a.second+b.second};
}
 
#define ll long long
#define pb push_back
#define f first 
#define s second 
#define fst first 
#define snd second 
#define ff first.first
#define fs first.second
#define sf second.first
#define ss second.second

#define fore(i,a,b) for(ll i = a; i < (ll)b; i++)
#define rfore(i, a, b) for(ll i = b - 1; i >= (ll)a; i--)
#define mm(a,b) memset(a , b , sizeof a) 
#define ALL(a) a.begin(),a.end() 
#define SZ(n) ((ll) (n).size())
 
#define infll (ll)(1e16+3)
#define infi  (ll)(1e9+4)
#define pi acos(-1) 
#define mod (ll)(1e9+7)
 
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b,a%b); } 
ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }
ll fpow(ll b, ll e, ll m = mod){int r=1;while(e){if(e&1)r=(r*b)%m;e/=2;b=(b*b)%m;}return r;}



int h,w;


vector<int> def[2] = {{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT},
                        {'w','s','a','d'}};



bool is_valid(pll a){
	return (a.f > 0 && a.s > 0 && a.f < h-1 && a.s < w-2);
}

int c;

int parse_in(vector<Snake>& s){
    int ch;
    int delay= 150000;
    fore(i,0,delay){
    	if((ch = getch()) != ERR)break;
    }
    if(ch == 'x')return 0;
    for(auto &x : s){
        x.parceMov(ch);
    }
    return 1;
}


void gen_apple(pair<int,int> &a, vector<Snake>& s){
    while(a == (pll) {-1,-1}){
    	a.f = rand()%(h-2);
    	a.s = rand()%(w-1);
    	if(a.f == 0)a.f=2;
    	if(a.s == 0)a.s=2;
    	if(a.f>1)a.f--;
        if(a.s>1)a.s--;
     	if(a.s%2 != 0)a.s++;
        bool b=false;
        for(auto &x : s){
            b |= x.hit(a);
        }
	    if(b){
	    	a = {-1,-1};
        }else{
       		sqr(a,RED);
        }
    }
}

void waitch(){
	int ch;
	while((ch = getch()) == ERR);
}


void insert_bd(Snake &snk){

    if(getenv("BD") != NULL){
        try {
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *resQ;
            sql::PreparedStatement *pstm;

           //Create a connection 
            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", getenv("USERBD"), getenv("PASSWORD"));
           //Connect to the MySQL test database 
            con->setSchema("snake");
            stmt = con->createStatement();
            pstm = con->prepareStatement("insert into snake_t (name,score) values(?,?)");
            pstm->setString(1,snk.getName());
            pstm->setInt(2,snk.getScore());
            pstm->executeUpdate();
            resQ = stmt->executeQuery("SELECT * FROM snake_t order by score desc limit 5 ");
            int i=1;
            while (resQ->next()) {
                cout << "\t... El " <<i<< "° mejor jugador es: ";
                // Access column data by numeric offset, 1 is the first column 
                cout << resQ->getString(2)<<" con un score de " << resQ->getString(3) << endl;
                i++;
            }   
      
            delete pstm;
            delete resQ;
            delete stmt;
            delete con;
        } catch (sql::SQLException &e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }        
    } else {
    	freopen("score.txt","a+",stdin);
        string s;
        vector<pair<int,string>> order;
        while(getline(cin,s)){
            stringstream sa(s);
            int score;
            string t; 
            sa>>score;
            getline(sa,t);
            reverse(ALL(t));
            while(t.back() == ' ')t.pop_back();
            reverse(ALL(t));
            order.pb(make_pair(score,t));
        }
        order.pb(make_pair(snk.getScore(),snk.getName()));
	fclose(stdin);
        int k = SZ(order);
	sort(order.begin(),order.end(),greater<pair<int,string>>());
        fore(i,0,min(5ll,SZ(order))){
            cout<<"\t... El "<<i+1<<"° mejor jugador es: ";
            cout << order[i].second<<" con un score de " << order[i].first << endl;
        }
        freopen("score.txt","w",stdout);
        fore(i,0,min(5ll,SZ(order))){
            cout<<order[i].first<<" "<<order[i].second<<endl;
        }
        fclose(stdout);
	cout<<k<<endl;

    }


}



int32_t main(int32_t argc, char const *argv[]){

    int n=1;
    n = atoi(argv[1]);
    n = min(max(n,1),2);

    vector<Snake> snakes; 
    vector<string> names(n);
    
    fore(i,0,n){
        if(atoi(argv[2])){
            cin>>names[i];
        }else{
            names[i]= "fede";
        }
    }

    initscr();
    auto a = init();
    h = a.f;
    w = a.s;
    bool run=1;

    fore(i,0,n){
        Snake aux(names[i],i+1,def[i],{h/(n+1),(w/(n+1))+i*(w/(n))});
        snakes.pb(aux);
    }

    pair<int,int> aple={-1,-1};
    gen_apple(aple, snakes);

	int res = 0;
    int win = 0;

    while(run) {
    	run = parse_in(snakes);

        fore(i,0,n){
            Snake &s = snakes[i];        
        	if(s.isValid(h,w)){
                int x = s.actPos(aple);
        		if(x==1){
                    aple = {-1,-1};
                    gen_apple(aple, snakes);
                }else if(!x){
                    run = 0;
                }
        	} else {
        		run = 0;
        	}
            if(!run && n != 1)win = !i;
        }
        
        fore(i,0,n){
            fore(j,0,n)if(i!=j){
                if(snakes[j].hit(snakes[i].getPos())){
                    win=j;
                    run = 0;
                }
            }
        }

        refresh();
    }
    fore(i,0,n){   
        wmove(stdscr,h/2+i,w/2);
        printw("score = %d", snakes[i].getScore());
    }

    waitch();
    waitch();    
    endwin(); // opuesto a initscr

    insert_bd(snakes[win]);



    return 0;    
} 

