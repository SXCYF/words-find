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


string trim(string str)  //ȥ���ַ����еĿո�
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
    //�����ַ���(��26��Ӣ����ĸ�Ĵ�Сд)

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
    cout<<"Ҫͳ�ƵĴʻ�������ַ�Ϊ��"<<endl;
    set<char>::iterator set_beg = letters.begin();

    while(set_beg!=letters.end())
    {
        cout<<*set_beg;
        if(*set_beg == 'Z'||*set_beg =='z')
            cout<<endl;
        ++set_beg;
    }

    //�����ַ�������
}


//type �����ļ������ͣ�'1' ����Ҫͳ�Ƶ��ļ��� '2' ����Ҫͳ���ļ�·�����ļ�
//file ָ���ļ�����ָ��
//letters  Ҫͳ�ƵĴʻ����������ַ���
int analytice(const char *file,set<char> letters,char type)
{

    ifstream stream_in;
    vector<string> vec_file;

    //��ȡ�����ļ�,����Ҫͳ�Ƶ��ļ�
    //cout<<"��ʼ��ȡ�ļ�Ŀ¼..."<<endl<<endl;
    cout<<endl;


    cout<<"Ҫͳ�Ƶ��ļ������£�"<<endl;
    if(type=='1')   //�����ĵ�
    {
        vec_file.push_back(file);
        cout<<"�ļ�: "<<file<<endl;
    }

    else            //����ĵ�
    {
        string str_file;
        stream_in.open(file,istream::in);
        int i=1;
        while (stream_in.good())
        {
            getline(stream_in,str_file);
            vec_file.push_back(str_file);
            cout<<"�ļ� "<<i<<": "<<str_file<<endl;
            ++i;
        }
            stream_in.close();
    }



    //cout<<endl<<"��ȡ�ļ�Ŀ¼����"<<endl<<endl;
    cout<<endl;
    //��ȡ�����ļ�����







    //�ж��ļ��Ƿ��𻵻򲻴���
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
            //cout<<"�ļ� "<<file_num<<": "<<*iter<< " ����! ��ȷ���ļ�·�����ļ����Ƿ���ȷ!"<<endl;
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
            cout<<"���棺�ļ�" <<vec_file[0]<<"�𻵻򲻴���"<<endl;
        }
        else if(file_good.size()==0&&type=='2')
        {
            cout<<file_good.size();
            cout<<"���棺�ļ�Ŀ¼�е������ļ�·����������������ȷ�������ļ�·��"<<endl;
            return 1;
        }
        else
        {
            cout<<"����, �����ļ��𻵻򲻴���!"<<endl;
            vector<string>::iterator iter_bad = file_bad.begin();
            while(iter_bad!=file_bad.end())
            {
                cout<<"�ļ�: "<<*iter_bad<<endl;
                ++iter_bad;
            }
            cout<<endl;

            cout<<"�����ļ��ļ�����ͳ��:"<<endl;
            vector<string>::iterator iter_good = file_good.begin();
            while(iter_good!=file_good.end())
            {
                cout<<"�ļ�: "<<*iter_good<<endl;
                ++iter_good;
            }
            cout<<endl;

            cout<<"�Ƿ����ͳ�ƣ�y/n"<<endl;

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
                    if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
                    {
                        //temp.pop_back();
                        //temp.erase(temp.end()-1);      //   ȥ�����з�
                        also_sta = temp;
                        break;
                    }

                }
                //also_sta = trim(also_sta);
                if(also_sta.size()!=1)
                    cout<<"�����������������룺y/n"<<endl;
                else if(also_sta[0]=='y')
                {
                    //copy(file_good.begin(),file_good.end(),back_inserter(vec_file));
                    vec_file.assign(file_good.begin(),file_good.end());
                    break;                 //����һ�µ�ͳ��
                }
                else if(also_sta[0]=='n')
                {
                    return 1;              //������һ�µ�ͳ��
                }
                else
                    cout<<"�����������������룺y/n"<<endl;
            }



        }

    }

    //����ͳ���ļ��еĵ���

    cout<<"��ʼ����ͳ���ļ��еĴʻ㼰����..."<<endl;
    iter = vec_file.begin();
    int file_num=1;
    while(iter!=vec_file.end())
    {
        cout<<"-----ͳ���ļ� "<<*iter<<endl;

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
    cout<<"ͳ���ļ��еĴʻ㼰��������..."<<endl;
    cout<<endl<<"�ܹ�ͳ�Ƶ�  "<<word_num_map.size()<<"  ������."<<endl<<endl;
    //ͳ���ļ��еĵ��ʽ���




    bool save_f = false;
    bool save_name_f =false;
    string save_in;
    string save_name;
    cout<<"�Ƿ񱣴��ļ���y/n"<<endl;
    while(1)
    {
        //cin>>save_in;
        //cin.sync();
        string temp;
        while(1)
        {
            getline(cin,temp);
            temp=trim(temp);
            if(temp.length())               //�������ַ�
            {
                //temp.pop_back();
                //temp.erase(temp.end()-1);      //   ȥ�����з�
                save_in = temp;
                break;
            }

        }

        //save_in = trim(save_in);
        if(save_in.size()!=1)
            cout<<"�����������������룺y/n"<<endl;
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
            cout<<"�����������������룺y/n"<<endl;
    }

    ofstream stream_out;
    string name;     //������浽���ļ���
    if(save_f)   //Ҫ�����ļ�
    {

        cout<<endl<<"������Ҫ������ļ�����"<<endl
                    <<"1��ʹ��Ĭ���ļ�����"<<endl
                    <<"2�����뱣���ļ�����"<<endl;
        string save_name_v;
        while(1)    //��ȡ�ļ����Ĵ�����
        {
            //cin>>save_name_v;
            //cin.sync();


            while(1)
            {
                string temp;
                getline(cin,temp);
                temp=trim(temp);
                if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
                {
                    //temp.pop_back();
                    //temp.erase(temp.end()-1);      //   ȥ�����з�
                    save_name_v = temp;
                    break;
                }

            }
            //save_name_v = trim(save_name_v);
            if(save_name_v.size()>1)
                cout<<"�����������������룺1/2"<<endl;
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
                cout<<"�����������������룺1/2"<<endl;
        }//��ȡ�ļ����Ĵ���������


        if(save_name_f)           //��Ĭ���ļ��������ļ�
            stream_out.open("ͳ�ƽ��.txt",ofstream::trunc);
        else                      //���뱣���ļ����ļ���
        {
            cout<<endl<<"�����뱣�������ļ���(������д�ļ�����׺)��"<<endl;

            while(1)
            {

                //string temp;
               // getline(cin,save_name);
                while(1)
                {
                    string temp;
                    getline(cin,temp);
                    temp=trim(temp);
                    if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
                    {

                        save_name = temp;   //ȡ���ļ���
                        break;
                    }
                }

                //temp=save_name;
                if(save_name.length())     //���ȴ����㣬�������зǿո��ַ�
                {
                    //temp.pop_back();
                    //temp.erase(temp.end()-1);      //   ȥ�����з�

                    ifstream stream_exist;
                    name = save_name + ".txt";
                    stream_exist.open(name.c_str(),ifstream::in);
                    if(stream_exist.fail())         //�����ʧ��˵�����ļ�������
                    {

                         stream_exist.close();
                         break;                   //ִ��������ļ�����
                    }
                    else                       //�������ѭ������
                    {
                        cout<<"�ļ�"<<name<<"�Ѿ����ڣ��Ƿ��串�ǣ�y/n"<<endl;
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
                                if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
                                {

                                    cover_v = temp;
                                    break;
                                }

                            }

                            //cout<<"ok"<<endl;

                            //cover_v = trim(cover_v);
                            if(cover_v.size()>1)
                                cout<<"�����������������룺y/n"<<endl;
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
                                cout<<"�����������������룺y/n"<<endl;
                        }

                        if(cover_f)
                            break;
                        else
                        {
                            save_name.clear();
                            stream_exist.close();
                            cout<<"�������������뱣����ļ���(������д�ļ�����׺):"<<endl;
                        }

                    }
                }

            }

            //stream_out.open(name.c_str(),ofstream::app);
        }


    }



    stream_out.open(name.c_str(),ofstream::trunc);
    stream_out<<"�ܹ�ͳ�Ƶ�  "<<word_num_map.size()<<"  �����ʣ�"<<endl;
    stream_out.close();

    cout<<endl<<"��ѡ��ͳ�ƴʻ�������ʽ:"<<endl
        <<"1�����ֵ�˳�������"<<endl
        <<"2�����ʻ�������ĸ�ĸ��������"<<endl
        <<"3�����ʻ���ֵ�Ƶ�������"<<endl;

    string num;
    //cin>>num;
    //getline(cin,num);
//     while(1)
//    {
//        string temp;
//        getline(cin,temp);
//        temp=trim(temp);
//        if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
//        {
//            //temp.pop_back();
//            //temp.erase(temp.end()-1);      //   ȥ�����з�
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
       // c = getc(stdin);           //��stdin�洢�������ַ�

        //cin>>num;
        //getline(cin,num);
         while(1)
        {
            string temp;
            getline(cin,temp);
            temp=trim(temp);
            if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
            {
               //temp.pop_back();
               //temp.erase(temp.end()-1);      //   ȥ�����з�
               num = temp;

               break;

            }

        }

        if(num.size()>3)
        {
             cout<<"���������������������:1/2/3/123�����(�����ظ�)"<<endl;
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
                cout<<"��Ҫ�����ظ������֣����������룺1/2/3/123�����(�����ظ�)"<<endl;
                continue;
            }



        }
        else
        {
            cout<<"���������������������:1/2/3/123�����(�����ظ�)"<<endl;
            continue;
        }


        //����Ϸ��������Ƿ�Ҫ�Զ��ַ�ʽ���
        if(num.size()>1)
        {

            cout<<"��ȷ��Ҫ�Զ��ַ�ʽ�����y/n"<<endl;
            bool y_n_f=false;
            while(1)
            {
                //cin>>str_ha;
                //cin.sync();
                string y_n;
                getline(cin,y_n);
                y_n = trim(y_n);
                if(y_n.size()>1)
                    cout<<"�����������������룺y/n"<<endl;
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
                    cout<<"�����������������룺y/n"<<endl;
            }

            if(y_n_f)
                break;       //�Զ��ַ�ʽ������
            else
            {
                cout<<"���������룺1/2/3/123�����(�����ظ�)"<<endl;
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
            //���ֵ�˳�����
            cout<<endl<<"���ʻ��ֵ������ͳ�ƽ�����£�"<<endl;
            stream_out.open(name.c_str(),ofstream::app);
            stream_out<<endl<<"���ʻ��ֵ������ͳ�ƽ�����£�"<<endl;
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
            //���ַ��������
            cout<<endl<<"���ʻ������ַ�����ͳ�ƽ�����£�"<<endl;
            stream_out.open(name.c_str(),ofstream::app);
            stream_out<<endl<<"���ʻ������ַ�����ͳ�ƽ�����£�"<<endl;
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
        //�����ֵ�Ƶ�����
            cout<<endl<<"���ʻ���ֵ�Ƶ��ͳ�ƽ�����£�"<<endl;
            stream_out.open(name.c_str(),ofstream::app);
            stream_out<<endl<<"���ʻ���ֵ�Ƶ��ͳ�ƽ�����£�"<<endl;
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
        cout<<endl<<"��ѡ������ͳ�Ƶ���Ŀ(���������)��"<<endl
            <<"1�������ļ���"<<endl
            <<"2������ļ���"<<endl;
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
                if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
                {
                    //temp.pop_back();
                    //temp.erase(temp.end()-1);      //   ȥ�����з�
                    str_ha = temp;
                    break;
                }

            }
            //str_ha = trim(str_ha);
            //cin.sync();
            if(str_ha.size()>1)
                cout<<"�����������������룺1/2"<<endl;
            else if(str_ha[0]=='1')
            {
                type = '1';
                cout<<endl<<"������Ҫͳ�Ƶ��ļ���(txt��ʽ)��"<<endl;
                break;
            }
            else if(str_ha[0]=='2')
            {
                type = '2';
                cout<<endl<<"���������Ҫͳ�Ƶ��ļ���·�����ļ���(txt��ʽ)��"<<endl;
                break;
            }
            else
                cout<<"�����������������룺1/2"<<endl;
        }




        //cin>>file_name;
        //cin.sync();
         //getline(cin,file_name);
         while(1)
         {
             string temp;
             getline(cin,temp);
             temp=trim(temp);
             if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
             {
                 //temp.pop_back();
                 //temp.erase(temp.end()-1);      //   ȥ�����з�
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
            cout<<"�����ļ������� �� ���ļ������ڣ�����������(�ļ���׺Ϊ��.txt��)��"<<endl;
            //cin>>file_name;
            //cin.sync();
             //getline(cin,file_name);
              while(1)
            {
                string temp;
                getline(cin,temp);
                temp=trim(temp);
                if(temp.length())     //���ȴ����㣬�������зǿո��ַ�
                {
                    //temp.pop_back();
                    //temp.erase(temp.end()-1);      //   ȥ�����з�
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
        cout<<endl<<"�Ƿ��������ļ�����ͳ�ƣ�y/n"<<endl;


        while(1)
        {
            //cin>>str_ha;
            //cin.sync();
            getline(cin,str_ha);
            str_ha = trim(str_ha);
            if(str_ha.size()>1)
                cout<<"�����������������룺y/n"<<endl;
            else if(str_ha[0]=='y')
            {
                flag = true;
                break;
            }
            else if(str_ha[0]=='n')
            {
                flag = false;
                exit(0);                   //ֱ���˳�����
            }
            else
                cout<<"�����������������룺y/n"<<endl;
        }


    }while(flag==true);

    return 0;
}












