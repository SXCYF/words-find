#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace::std;


string trim(string str)  //去掉字符串中的空格
{
    string temp;
    size_t t = str.size();
    size_t i=0;

    while(i<t)
    {
        if(str[i]!='\t'&&str[i]!=' ')
            temp.push_back(str[i]);
        ++i;
    }
    return temp;

}

bool more_time(pair<string,int> vec_1,pair<string,int> vec_2)
{
   return (vec_1.second > vec_2.second);

};

bool less_lett(pair<string,int> vec_1,pair<string,int> vec_2)
{
    return (vec_1.first.size()<vec_2.first.size());

};


void constr_lett_set(set<char> &letters)
{
    //构建字符集(即26个英文字母的大小写)

    char letter('a');
    letters.insert(letter);
    for(int i=0;i<25;++i)
    {
        letter=letter+1;
        letters.insert(letter);

    }
    letter = 'A';
    letters.insert(letter);
    for(int i=0;i<25;++i)
    {
        letter=letter+1;
        letters.insert(letter);

    }
    cout<<"要统计的词汇包含的字符为："<<endl;
    set<char>::iterator set_beg = letters.begin();

    while(set_beg!=letters.end())
    {
        cout<<*set_beg;
        if(*set_beg == 'Z'||*set_beg =='z')
            cout<<endl;
        ++set_beg;
    }

    //构建字符集结束
}


//type 输入文件的类型：'1' 单个要统计的文件、 '2' 包含要统计文件路径的文件
//file 指向文件名的指针
//letters  要统计的词汇所包含的字符集
int analytice(const char *file,set<char> letters,char type)
{

    ifstream stream_in;
    vector<string> vec_file;

    //读取配置文件,即需要统计的文件
    //cout<<"开始读取文件目录..."<<endl<<endl;
    cout<<endl;


    cout<<"要统计的文件名如下："<<endl;
    if(type=='1')   //单个文档
    {
        vec_file.push_back(file);
        cout<<"文件: "<<file<<endl;
    }

    else            //多个文档
    {
        string str_file;
        stream_in.open(file,istream::in);
        int i=1;
        while (stream_in.good())
        {
            getline(stream_in,str_file);
            vec_file.push_back(str_file);
            cout<<"文件 "<<i<<": "<<str_file<<endl;
            ++i;
        }
            stream_in.close();
    }



    //cout<<endl<<"读取文件目录结束"<<endl<<endl;
    cout<<endl;
    //读取配置文件结束







    //判断文件是否损坏或不存在
    map<string,int>  word_num_map;

    vector<string>::iterator iter = vec_file.begin();
    vector<string> file_bad;
    vector<string> file_good;
    while(iter!=vec_file.end())
    {
        string file_name(*iter);
        stream_in.open(file_name.c_str(),istream::in);
        if(stream_in.fail())
        {
            //cout<<"文件 "<<file_num<<": "<<*iter<< " 出错! 请确认文件路径及文件名是否正确!"<<endl;
            file_bad.push_back(*iter);

        }
        else
            file_good.push_back(*iter);
        ++iter;
        stream_in.close();
    }

    if(file_good.size()<vec_file.size())
    {
//        cout<<file_good.size();
//        cout<<file_bad.size();
//        cout<<type;
        if(file_good.size()==0&&type=='1')
        {
            cout<<"警告：文件" <<vec_file[0]<<"损坏或不存在"<<endl;
        }
        else if(file_good.size()==0&&type=='2')
        {
            cout<<file_good.size();
            cout<<"警告：文件目录中的所有文件路径均错误，请您重新确认所有文件路径"<<endl;
            return 1;
        }
        else
        {
            cout<<"警告, 以下文件损坏或不存在!"<<endl;
            vector<string>::iterator iter_bad = file_bad.begin();
            while(iter_bad!=file_bad.end())
            {
                cout<<"文件: "<<*iter_bad<<endl;
                ++iter_bad;
            }
            cout<<endl;

            cout<<"以下文件文件可以统计:"<<endl;
            vector<string>::iterator iter_good = file_good.begin();
            while(iter_good!=file_good.end())
            {
                cout<<"文件: "<<*iter_good<<endl;
                ++iter_good;
            }
            cout<<endl;

            cout<<"是否进行统计？y/n"<<endl;

            string also_sta;
            vec_file.clear();
            while(1)
            {
                //getline(cin,also_sta);
                 while(1)
                {
                    string temp;
                    getline(cin,temp);
                    temp=trim(temp);
                    if(temp.length())     //长度大于零，即输入有非空格字符
                    {
                        //temp.pop_back();
                        //temp.erase(temp.end()-1);      //   去掉换行符
                        also_sta = temp;
                        break;
                    }

                }
                //also_sta = trim(also_sta);
                if(also_sta.size()!=1)
                    cout<<"输入有误！请重新输入：y/n"<<endl;
                else if(also_sta[0]=='y')
                {
                    //copy(file_good.begin(),file_good.end(),back_inserter(vec_file));
                    vec_file.assign(file_good.begin(),file_good.end());
                    break;                 //进行一下的统计
                }
                else if(also_sta[0]=='n')
                {
                    return 1;              //不进行一下的统计
                }
                else
                    cout<<"输入有误！请重新输入：y/n"<<endl;
            }



        }

    }

    //初步统计文件中的单词

    cout<<"开始初步统计文件中的词汇及数量..."<<endl;
    iter = vec_file.begin();
    int file_num=1;
    while(iter!=vec_file.end())
    {
        cout<<"-----统计文件 "<<*iter<<endl;

        string file_name(*iter);
        stream_in.open(file_name.c_str(),istream::in);
        string str;
        while (stream_in.good())
        {
            stream_in>>str;
            size_t lett_num = str.size();
            //cout<<str<<endl;
            string word;
            for(size_t i=0;i<lett_num;i++)
            {
                if(letters.count(str[i]))
                    word.push_back(tolower(str[i]));
                else if(i!=0&&i!=lett_num)
                {
                    size_t j = word.size();
                    if(j>1)
                    {
                         ++word_num_map[word];

                    }
                    word.clear();
                }

            }
            size_t j = word.size();
            if(j>1)
            {
                ++word_num_map[word];
                word.clear();
            }


            //cout<<endl;
        }
          ++iter;
          ++file_num;
          stream_in.close();
    }
    cout<<"统计文件中的词汇及数量结束..."<<endl;
    cout<<endl<<"总共统计到  "<<word_num_map.size()<<"  个单词."<<endl<<endl;
    //统计文件中的单词结束




    bool save_f = false;
    bool save_name_f =false;
    string save_in;
    string save_name;
    cout<<"是否保存文件？y/n"<<endl;
    while(1)
    {
        //cin>>save_in;
        //cin.sync();
        string temp;
        while(1)
        {
            getline(cin,temp);
            temp=trim(temp);
            if(temp.length())               //有输入字符
            {
                //temp.pop_back();
                //temp.erase(temp.end()-1);      //   去掉换行符
                save_in = temp;
                break;
            }

        }

        //save_in = trim(save_in);
        if(save_in.size()!=1)
            cout<<"输入有误！请重新输入：y/n"<<endl;
        else if(save_in[0]=='y')
        {
            save_f = true;
            break;
        }
        else if(save_in[0]=='n')
        {
            save_f = false;
            break;
        }
        else
            cout<<"输入有误！请重新输入：y/n"<<endl;
    }

    ofstream stream_out;
    string name;     //结果保存到的文件名
    if(save_f)   //要保存文件
    {

        cout<<endl<<"请输入要保存的文件名："<<endl
                    <<"1、使用默认文件名；"<<endl
                    <<"2、输入保存文件名；"<<endl;
        string save_name_v;
        while(1)    //获取文件名的处理方法
        {
            //cin>>save_name_v;
            //cin.sync();


            while(1)
            {
                string temp;
                getline(cin,temp);
                temp=trim(temp);
                if(temp.length())     //长度大于零，即输入有非空格字符
                {
                    //temp.pop_back();
                    //temp.erase(temp.end()-1);      //   去掉换行符
                    save_name_v = temp;
                    break;
                }

            }
            //save_name_v = trim(save_name_v);
            if(save_name_v.size()>1)
                cout<<"输入有误！请重新输入：1/2"<<endl;
            else if(save_name_v[0]=='1')
            {
                save_name_f = true;
                break;
            }
            else if(save_name_v[0]=='2')
            {
                 save_name_f = false;

                //cin>>save_name;
                //cin.sync();
                //getline(cin,save_name);


                break;
            }
            else
                cout<<"输入有误！请重新输入：1/2"<<endl;
        }//获取文件名的处理方法结束


        if(save_name_f)           //用默认文件名保存文件
            stream_out.open("统计结果.txt",ofstream::trunc);
        else                      //输入保存文件的文件名
        {
            cout<<endl<<"请输入保存结果的文件名(不用填写文件名后缀)："<<endl;

            while(1)
            {

                //string temp;
               // getline(cin,save_name);
                while(1)
                {
                    string temp;
                    getline(cin,temp);
                    temp=trim(temp);
                    if(temp.length())     //长度大于零，即输入有非空格字符
                    {

                        save_name = temp;   //取得文件名
                        break;
                    }
                }

                //temp=save_name;
                if(save_name.length())     //长度大于零，即输入有非空格字符
                {
                    //temp.pop_back();
                    //temp.erase(temp.end()-1);      //   去掉换行符

                    ifstream stream_exist;
                    name = save_name + ".txt";
                    stream_exist.open(name.c_str(),ifstream::in);
                    if(stream_exist.fail())         //如果打开失败说明该文件不存在
                    {

                         stream_exist.close();
                         break;                   //执行下面的文件保存
                    }
                    else                       //否则继续循环输入
                    {
                        cout<<"文件"<<name<<"已经存在，是否将其覆盖？y/n"<<endl;
                        bool cover_f = false;
                        string cover_v;
                        while(1)
                        {
                            //cin>>str_ha;
                            //cin.sync();
                            //getline(cin,cover_v);
                            while(1)
                            {
                                string temp;
                                getline(cin,temp);
                                temp=trim(temp);
                                if(temp.length())     //长度大于零，即输入有非空格字符
                                {

                                    cover_v = temp;
                                    break;
                                }

                            }

                            //cout<<"ok"<<endl;

                            //cover_v = trim(cover_v);
                            if(cover_v.size()>1)
                                cout<<"输入有误！请重新输入：y/n"<<endl;
                            else if(cover_v[0]=='y')
                            {
                                cover_f = true;
                                break;
                            }
                            else if(cover_v[0]=='n')
                            {
                                cover_f = false;
                                break;

                            }
                            else
                                cout<<"输入有误！请重新输入：y/n"<<endl;
                        }

                        if(cover_f)
                            break;
                        else
                        {
                            save_name.clear();
                            stream_exist.close();
                            cout<<"请重新输入您想保存的文件名(不用填写文件名后缀):"<<endl;
                        }

                    }
                }

            }

            //stream_out.open(name.c_str(),ofstream::app);
        }


    }



    stream_out.open(name.c_str(),ofstream::trunc);
    stream_out<<"总共统计到  "<<word_num_map.size()<<"  个单词："<<endl;
    stream_out.close();

    cout<<endl<<"请选择统计词汇的输出方式:"<<endl
        <<"1、按字典顺序输出；"<<endl
        <<"2、按词汇所含字母的个数输出；"<<endl
        <<"3、按词汇出现的频率输出；"<<endl;

    string num;
    //cin>>num;
    //getline(cin,num);
//     while(1)
//    {
//        string temp;
//        getline(cin,temp);
//        temp=trim(temp);
//        if(temp.length())     //长度大于零，即输入有非空格字符
//        {
//            //temp.pop_back();
//            //temp.erase(temp.end()-1);      //   去掉换行符
//            num = temp;
//            break;
//        }
//
//    }
    //num = trim(num);
    //cin.sync();

    bool all_num_f = true;

    while(1)
    {
       // c = getc(stdin);           //流stdin存储着两个字符

        //cin>>num;
        //getline(cin,num);
         while(1)
        {
            string temp;
            getline(cin,temp);
            temp=trim(temp);
            if(temp.length())     //长度大于零，即输入有非空格字符
            {
               //temp.pop_back();
               //temp.erase(temp.end()-1);      //   去掉换行符
               num = temp;

               break;

            }

        }

        if(num.size()>3)
        {
             cout<<"您的输入错误！请重新输入:1/2/3/123的组合(不可重复)"<<endl;
             continue;
        }

        for(size_t i=0;i<num.size();i++)
        {
            if(num[i]>'3'||num[i]<'1')
            {
                all_num_f = false;


                break;
            }
        }
        //cout<<num.size()<<endl;
        if(all_num_f)
        {
            if( ((num.size()==2)&&(num[0]==num[1])) || (num.size()==3&&((num[0]==num[1])||(num[1]==num[2])||(num[0]==num[2]))))
            {
                cout<<"不要输入重复的数字，请重新输入：1/2/3/123的组合(不可重复)"<<endl;
                continue;
            }



        }
        else
        {
            cout<<"您的输入错误！请重新输入:1/2/3/123的组合(不可重复)"<<endl;
            continue;
        }


        //输入合法，提醒是否要以多种方式输出
        if(num.size()>1)
        {

            cout<<"您确定要以多种方式输出吗？y/n"<<endl;
            bool y_n_f=false;
            while(1)
            {
                //cin>>str_ha;
                //cin.sync();
                string y_n;
                getline(cin,y_n);
                y_n = trim(y_n);
                if(y_n.size()>1)
                    cout<<"输入有误！请重新输入：y/n"<<endl;
                else if(y_n[0]=='y')
                {
                    y_n_f = true;
                    break;
                }
                else if(y_n[0]=='n')
                {
                    y_n_f = false;
                    break;
                }
                else
                    cout<<"输入有误！请重新输入：y/n"<<endl;
            }

            if(y_n_f)
                break;       //以多种方式混合输出
            else
            {
                cout<<"请重新输入：1/2/3/123的组合(不可重复)"<<endl;
            }
        }
        else
            break;





    }



    //num = trim(num);
    //cin.sync();
    //cout<<num<<endl;

    for(size_t i=0;i<num.size();i++)
    {
        if(num[i]=='1')
        {
            //按字典顺序输出
            cout<<endl<<"按词汇字典排序的统计结果如下："<<endl;
            stream_out.open(name.c_str(),ofstream::app);
            stream_out<<endl<<"按词汇字典排序的统计结果如下："<<endl;
            map<string,int>::iterator iter_map = word_num_map.begin();
            while (iter_map!=word_num_map.end())
            {

                cout<<iter_map->first<<"  "<<iter_map->second<<endl;
                if(save_f&&stream_out.good())
                    stream_out<<iter_map->first<<"  "<<iter_map->second <<endl;
                ++iter_map;

            }
            stream_out.close();
        }
        else if(num[i] == '2')
        {
            //按字符个数输出
            cout<<endl<<"按词汇所含字符个数统计结果如下："<<endl;
            stream_out.open(name.c_str(),ofstream::app);
            stream_out<<endl<<"按词汇所含字符个数统计结果如下："<<endl;
            vector<pair<string,int> > word_num_vec;
            copy(word_num_map.begin(),word_num_map.end(),back_inserter(word_num_vec));
            sort(word_num_vec.begin(),word_num_vec.end(),less_lett);
            vector<pair<string,int> >::iterator iter_vec = word_num_vec.begin();

            while (iter_vec!=word_num_vec.end())
            {

                //stream_out<<'+'<<iter_vec->first<<endl<<"$1"<<endl;
                cout<<iter_vec->first<<"  "<<iter_vec->second <<endl;
                if(save_f&&stream_out.good())
                    stream_out<<iter_vec->first<<"  "<<iter_vec->second <<endl;
                ++iter_vec;
            }
            stream_out.close();

        }
        else if(num[i]=='3')
        {
        //按出现的频率输出
            cout<<endl<<"按词汇出现的频率统计结果如下："<<endl;
            stream_out.open(name.c_str(),ofstream::app);
            stream_out<<endl<<"按词汇出现的频率统计结果如下："<<endl;
            vector<pair<string,int> > word_num_vec;
            copy(word_num_map.begin(),word_num_map.end(),back_inserter(word_num_vec));
            stable_sort(word_num_vec.begin(),word_num_vec.end(),more_time);
            vector<pair<string,int> >::iterator iter_vec = word_num_vec.begin();

            while (iter_vec!=word_num_vec.end())
            {
                //stream_out<<iter_vec->first<<"  "<<iter_vec->second <<endl;
                cout<<iter_vec->first<<"  "<<iter_vec->second <<endl;
                if(save_f&&stream_out.good())
                    stream_out<<iter_vec->first<<"  "<<iter_vec->second <<endl;
                ++iter_vec;
            }
            stream_out.close();
        }

    }

    return 0;
}



int main()
{
    set<char> letters;
    constr_lett_set(letters);

    string file_name;
    char type;
    bool flag = false;
    do{
        cout<<endl<<"请选择您好统计的项目(下面的数字)："<<endl
            <<"1、单个文件；"<<endl
            <<"2、多个文件；"<<endl;
        string str_ha;
        while(1)
        {
            //cin>>str_ha;
            //getline(cin,str_ha);
             while(1)
            {
                string temp;
                getline(cin,temp);
                temp=trim(temp);
                if(temp.length())     //长度大于零，即输入有非空格字符
                {
                    //temp.pop_back();
                    //temp.erase(temp.end()-1);      //   去掉换行符
                    str_ha = temp;
                    break;
                }

            }
            //str_ha = trim(str_ha);
            //cin.sync();
            if(str_ha.size()>1)
                cout<<"输入有误！请重新输入：1/2"<<endl;
            else if(str_ha[0]=='1')
            {
                type = '1';
                cout<<endl<<"请输入要统计的文件名(txt格式)："<<endl;
                break;
            }
            else if(str_ha[0]=='2')
            {
                type = '2';
                cout<<endl<<"请输入包含要统计的文件的路径的文件名(txt格式)："<<endl;
                break;
            }
            else
                cout<<"输入有误！请重新输入：1/2"<<endl;
        }




        //cin>>file_name;
        //cin.sync();
         //getline(cin,file_name);
         while(1)
         {
             string temp;
             getline(cin,temp);
             temp=trim(temp);
             if(temp.length())     //长度大于零，即输入有非空格字符
             {
                 //temp.pop_back();
                 //temp.erase(temp.end()-1);      //   去掉换行符
                 file_name = temp;
                 break;
             }

         }
         //file_name = trim(file_name);
        ifstream stream_judge;
        stream_judge.open(file_name.c_str(),ifstream::in);
        while( !stream_judge.good())
        {
            stream_judge.close();
            cout<<"输入文件名错误 或 该文件不存在！请重新输入(文件后缀为“.txt”)："<<endl;
            //cin>>file_name;
            //cin.sync();
             //getline(cin,file_name);
              while(1)
            {
                string temp;
                getline(cin,temp);
                temp=trim(temp);
                if(temp.length())     //长度大于零，即输入有非空格字符
                {
                    //temp.pop_back();
                    //temp.erase(temp.end()-1);      //   去掉换行符
                    file_name = temp;
                    break;
                }

            }
           //file_name = trim(file_name);
            stream_judge.open(file_name.c_str(),ifstream::in);
        }
        stream_judge.close();
        analytice(file_name.c_str(),letters,type);
        file_name.clear();
        cout<<endl<<"是否还有其他文件进行统计？y/n"<<endl;


        while(1)
        {
            //cin>>str_ha;
            //cin.sync();
            getline(cin,str_ha);
            str_ha = trim(str_ha);
            if(str_ha.size()>1)
                cout<<"输入有误！请重新输入：y/n"<<endl;
            else if(str_ha[0]=='y')
            {
                flag = true;
                break;
            }
            else if(str_ha[0]=='n')
            {
                flag = false;
                exit(0);                   //直接退出程序
            }
            else
                cout<<"输入有误！请重新输入：y/n"<<endl;
        }


    }while(flag==true);

    return 0;
}












