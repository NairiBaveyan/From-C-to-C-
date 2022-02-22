#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>


std::map<int,std::string> classn;
const int Index = 0;

class Utility
{
public:
    void printVtable(std::vector<std::string> &);
    void printMain(int , std::vector<std::string>&);
    void printIncludes(std::vector<std::string> &);
};
class textParcer
{
public:
    void functionsParcer(std::string & str);
    void classParcer(std::string & str);
    void coutInOtherFile();
    void setClassName(std::string&);
    int getvirtualIndex(){return this->virtualIndex;}
private:
    std::vector<std::string> c_style_fanctions;
    std::vector<std::string> c_struct;
    std::string className = " ";
    int index = 0;
    int virtualIndex = 0;    
};
void Utility::printMain(int index, std::vector<std::string>& vec )
{
    
    std::fstream fout;
    for(int i = index+1; i < vec.size();++i)
    {
        if(vec[i].find('(') != -1 && vec[i].find(')') != -1)
        {
            int pos = vec[i].find('.');
            std::string c__Text = vec[i];
            std::string cText = "&";
            std::string c_name;
            for(int i = 0; i < pos;++i)
            {
                cText+= c__Text[i];
                c__Text.erase(0,1);
            }
            c_name = cText;
            c_name.erase(0,1);
            for(int i = 0; i < c_name.size();++i)
             c_name[i] = toupper(c_name[i]);
            
            c__Text.erase(0,1);
            c__Text.insert(c__Text.find('('),c_name);
            if((c__Text.find(')')-c__Text.find('(')) ==1)
            {
                c__Text.insert(c__Text.find('(')+1,cText);
            }else{
                c__Text.insert(c__Text.find('(')+1,cText+",");
            }
            vec[i] =  c__Text;    
            
        }

    }
    std::string type_info;
    for(int i = index+1; i < vec.size();++i)
    {    
         int pos = vec[i].find('*');
         int pos_ = vec[i].find('(');
         int pos__ = vec[i].find(')');
         int pos___ = vec[i].find("->");
         int obj = vec[i].find('&');

         if(pos !=-1 ){
            type_info[0] = vec[i][obj+1];
            type_info[0] = toupper(type_info[0]);
            vec[i].erase(vec[i].begin(),vec[i].begin()+obj);
            vec[i].insert(0,"vt.vPtr = (void*)");   
         }
         
        if(pos_!=-1 &&  pos___ != -1)
        {   

               //std::cout << type_info[0];
            vec[i].erase(vec[i].begin(),vec[i].begin()+pos___+2);
            int pos = vec[i].find('&');
            vec[i].erase(pos,1);
            vec[i].insert(pos-1,1,type_info[0]);
            vec[i].insert(pos+1,1,'(');
            vec[i].insert(pos+2,1,type_info[0]);
            vec[i].insert(pos+3,1,'*');
            vec[i].insert(pos+4,1,')'); 
            std::string __type = "vt.vPtr";
            vec[i].insert(pos+5,__type);

        }
            
    }
    fout.open("c_style.cpp",std::ios_base::app);
    for(int i = index; i < vec.size();++i)
    {
        fout  <<  vec[i] << std::endl;
    }
    fout.close();

}

void Utility::printVtable(std::vector<std::string> & vt)
{
    std::fstream fout;
    fout.open("c_style.cpp",std::ios_base::app);
    for(int i = 0; i < vt.size();++i)
    {
        fout  <<  vt[i] << std::endl;        
    }
    fout << std::endl;
    fout.close();
}

void Utility::printIncludes(std::vector<std::string> & includes)
{
    std::fstream fout;
    fout.open("c_style.cpp",std::ios_base::app);
    for(int i = 0; i < includes.size();++i)
    {
        fout  <<  includes[i] << std::endl;
    }
    fout << std::endl;
    fout.close();
}

void textParcer::functionsParcer(std::string & str)
{
    int vPos = str.find("virtual");
    if(vPos!=-1){
    this->virtualIndex++;
    str.erase(vPos,7);
    }
    int pos = str.find('(');
    int pos_ = str.find(')');
    if(pos == -1 && pos_ == -1){
        return;
    }else{
        int i = 0;
            
        if(pos_- pos == 1)
        {
             
             int p = str.find("this->");
                if(p!=-1){
                str.erase(p,6);
                str.insert(p,"that->");
            }
             
             str.insert(pos+1,classn[i]+" *that ");
             str.insert(pos,classn[i]);
             
            this->c_style_fanctions.push_back(str);
            
                ++i;
        }else{
            int p = str.find("this->");
            if(p!=-1){
            str.erase(p,6);
            str.insert(p,"that->");
            }
            
            str.insert(pos+1,classn[i]+" *that, ");
            str.insert(pos,classn[i]);
            this->c_style_fanctions.push_back(str);
            ++i;
        }

    }
}

void textParcer::classParcer(std::string & str)
{
    
    std::string object;

    int i = 0;
    if(str.find(":public") != -1 || str.find(":private") != -1)
    {
        int pos = str.find(":public");
        
        for(int i = pos+8;i <= str.size()-1;++i)
        {
            object += str[i];
        }
        object;
        str.erase(pos,str.size());
        this->className = object+" obj;";
        this->index++;
    
    }
    if(str == "public:"||str == "private:"){
        if(this->index == 1){
            str = "\t"+this->className;
            this->index--;
        }
        
    }
    int classNamePos = str.find("class");
    if(classNamePos !=-1)
    {
        str.erase(0,6);
        classn[0] =  str;
        str = "struct "+str;    
    }
    
    int pos_ = str.find('(');
    int pos = str.find(')');
    if(pos_== -1 && pos == -1 && str != "private:" && str != "public:")
    {
            this->c_struct.push_back(str);
    }   
}

void textParcer::coutInOtherFile(){
    std::fstream fout;
    fout.open("c_style.cpp",std::ios_base::app);
    
    for(int i = 0; i < this->c_struct.size();++i)
    {
        fout << c_struct[i] << std::endl;
    }
    for(int i = 0; i < this->c_style_fanctions.size();++i)
    {
        fout <<  c_style_fanctions[i] << std::endl; 
    }
    std::cout << std::endl;
    fout.close();
}

int main(){
    
    
    std::string line;
    std::vector<std::string> vec;
    std::vector<std::string> main;
    std::vector<std::string> includes;
    std::fstream file;
    std::string path;
    int index = 0;
    std::cout <<  "give the file path";
    std::cout << std::endl;
    std::cin >> path;
    file.open(path);
    if(file.is_open())
    {
        while(!file.eof()){
            std::getline(file,line);
            if(line.find("class")!=-1){
                std::string tmp = line;
                tmp.erase(0,6);
                classn.emplace(index,tmp);
                ++index;
            
            }
            if(line.find('#')!=-1){
                includes.push_back(line);
            }else{
            vec.push_back(line);
            }   
        }
    }
    else
    {
        std::cout << "This File is invalid" << std::endl;
        std::cout << "Provide the full path of the file, please!";
        std::exit(0);
    }
    file.close();
    std::vector<std::string> vt;
    std::string vTable;
    file.open("struct.cpp");
    if(file.is_open())
    {
        while(!file.eof()){
            std::getline(file,vTable);
            vt.push_back(vTable);
        }
    }
    file.close();
    std::cout << std::endl;
   
    int mainIndex = 0; 
    std::system("g++ main.cpp -o Svax.out");
    std::system("rm Svax.out");
    textParcer p;
    Utility u;
    u.printIncludes(includes);
    for(int i = 0; i < vec.size(); ++i)
    {   
        if(vec[i].find("main()")!=-1){
            mainIndex = i;
            break;
        }
        p.classParcer(vec[i]);
        p.functionsParcer(vec[i]);
    }
    
    p.coutInOtherFile();
    if(p.getvirtualIndex()!=0){
    u.printVtable(vt);
    }
    u.printMain(mainIndex,vec);

    
    return 0;
}

