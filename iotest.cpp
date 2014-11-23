#include <iostream>
#include <unistd.h>//for sleep()
using namespace std;

int main()
{
  char c;

  //In the case you expect at least twice,
  //you have to unify the requirement function
  // to "cin.get" or "cin.getline"
  //Otherwise you see bus error in the case without cin.clear(),
  //and even if you added cin.clear() you see segmentation fault
  //after you put some letter for the first requirement
  //
  // cout <<"Put something"<<endl;
  // cin >>c;
  // cout <<"you put  "<<c<<endl;
  // cin.clear();

  //you can define char in both ways.
//  char* name;
  char name[128];

  while(1)
  {
    cout <<"Put your name"<<endl;
    // getline(cin , name);
    /*cin.get passes compilation, but
      without any chance of giving the second arg,
      it keeps on putting cout forever...*/
    //cin.get(name,128,'\n');
    cin>>name;
    cin.clear();
    if(name[0]=='x')break;
    cout <<"Hello, "<<name<<"!"<<endl;
    char copiedname[128];
    strcpy(copiedname,name);
    cout << "again I say hello "<<copiedname<<endl;
    sleep(3);
    

  }
}
