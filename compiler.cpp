#include<iostream>
#include<string>
#include<queue> 

using namespace std;
string keywords[29] ={
    "read"  ,	"print" , 	"if" ,	"then", 	"else" ,	"endif"
 ,"while",	"do",	"endwhile",	"breakpoint",	"continue",  "main"	,"return"	,"decl",	"enddecl",	"create",
"open"  , "write" ,	"seek",	"read"	,"close"	,"delete" ,
"fork",	"exec",	"exit","break"	,	"real" , "integer", "string"  // 26 27 28
};


string readfile(char f[] )
{
    char ch; 
    string r;
   FILE * fp = fopen(f , "r");

    if (fp == NULL)
    {
        cout << "Error while opening the file.\n";
        return r; 
    }

    

    
    while ((ch = fgetc(fp)) != EOF)
        r.push_back(ch);

    fclose(fp);

    return r; 
    
}

int  is_intailize( string  c )
{
    for (int i = 0; i < c.length(); i++)
    {
        if (c[i] == '=') return 1;
        else if (c[i] == ';') return 0;
        else if (c[i] == '(') return 2;  // function identifier
        else if (c[i] == ')') return 3; 
    }

    return 4; 
}

void  writefile(queue<string> s , char file_name[])
{
    FILE* fp = fopen(file_name, "w");

    if (fp == NULL)
    {
        fprintf(fp, "%s","EMPTY...\n"  ); 
        return;
    }


    while (!s.empty())
    {
       fprintf(fp , "      %s\n" ,  s.front().data());
       fprintf(fp, "_____________________________\n\n" );
        s.pop();
    }
    
    cout << "Write is done ...\n";
    fclose(fp);

    return;

}

bool comment(string s)
{
   bool flag = false; 

   for (int i = 0; i < s.length()-1; i++)
   {
       if (s[i] == '/' && s[i + 1] == '/')
       {
           flag = true; 
           break;
      }
   }

   return flag; 
}

string cut(string s ,char x)
{
    string temp;
    for (int i = 0; s[i] != x; i++)
    {
        temp += s[i];
    }
    return temp;
}

bool nl(string s)
{
    bool flag = false;

    for (int i = 0; i < s.length() ; i++)
    {
        if (s[i] == '\n' )
        {
            flag = true;
            break;
        }
    }

    return flag;
}

bool space(string s)
{
    bool flag = false;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            flag = true;
            break;
        }
    }

    return flag;
}

bool tap(string s)
{
    bool flag = false;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '\t')
        {
            flag = true;
            break;
        }
    }

    return flag;
}

void text_processor(string & s)
{
    //Comment trimming
    while (comment(s))
    {
        int c = 0;
        for (int i = s.find("//"); i < s.length(); i++)
        {
            c++; 
            if (s[i] == '\n') break; 
        }
         
        s.erase(s.find("//"), c);
   }

    //space & endl trimming

    while (nl(s))
    {
        
            s.erase(s.find('\n') , 1);
        
    }

    while (space(s))
    {

        s.erase(s.find(' '), 1);

    }
    
    while (tap(s))
    {

        s.erase(s.find('\t'), 1);

    }

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] += 32; 
        }
    }
   
       

      
    
}

int opr_s(string s)
{
   
   

        if (s.length() == 1)
        {
           
             
            if (s[0] == '(' || s[0] == ')' || s[0] == '{' || s[0] == '}' || s[0] == '[' || s[0] == ']' || s[0] == '/' || s[0] == '*' ||
                s[0] == '+' || s[0] == '-' || s[0] == '%' || s[0] == ';' || s[0] == '<' || s[0] == '>' || s[0] == '=' || s[0] == '!')
            {

                return 1; 
            }
            else
            {
                return 0; 

            }


        }
        else
        {
            if (s[0] == '(' || s[0] == ')' || s[0] == '{' || s[0] == '}' || s[0] == '[' || s[0] == ']' || s[0] == '/' || s[0] == '*' ||
                s[0] == '+' || s[0] == '-' || s[0] == '%' || s[0] == ';' || s[0]==':')
            {
                
                return 1;
            }
            else if (s.substr(0, 2) == "&&" || s.substr(0, 2) == "||")
            {

                return 2;
            }
            else if (s[0] == '<' || s[0] == '>' || s[0] == '=' || s[0] == '!')
            {
                if (s[1] == '=')
                {

                    return 2;
                }


                return 1;

            }


            return 0;
        }

}

int key_s( string s )
{
     for (int i = 0; i < 29; i++)
     {

            if (s.substr(0, keywords[i].length()) == keywords[i])
            {
                return i ;
            }
     }
   

    return -1;
}




queue<string>  get_tokens(string c)
{   
   
   
    queue<string> container;

    while (c.length())
    {

       
        if (opr_s(c) == 1)
        {
           
            string temp; 
           temp.push_back(c[0]); 
           container.push(temp); 
                c = c.substr(1);
                
         
         
        }
        else if (opr_s(c) == 2)
        {
            string temp;
            temp = c.substr(0, 2); 
            container.push(temp);
            c = c.substr(2); 
        }
        else  if (key_s(c) > -1)
        {
            int index = key_s(c);
            if (index > 25)
            {
                string temp; 
                string vn;
                temp = keywords[index]; 
                container.push(temp);
                c = c.substr(keywords[index].length());
                
                if (is_intailize(c) == 1)
                {
                    vn = cut(c, '=');
                    temp = "identifier_litteral   ";
                    temp += vn;
                    container.push(temp);
                    c = c.substr(c.find('='));

                    container.push("=");
                    c = c.substr(1);



                    vn = cut(c, ';');
                    switch (index)
                    {
                    case 26:
                    {
                        temp = "Real_litteral   ";
                        temp += vn;
                        container.push(temp);
                        break;
                    }
                    case 27:
                    {

                        temp = "Integer_litteral   ";
                        temp += vn;
                        container.push(temp);
                        break;
                    }
                    case 28:
                    {
                        temp = "String_litteral   ";
                        temp += vn;
                        container.push(temp);
                        break;
                    }
                    }
                    c = c.substr(c.find(';'));


                }
                else if (is_intailize(c) == 0)
                {
                    vn = cut(c, ';');
                    temp = "identifier_litteral   ";
                    temp += vn;
                    container.push(temp);
                    c = c.substr(c.find(';'));
                }
                else if (is_intailize(c) == 2)
                {
                    vn = cut(c, '(');
                    temp = "identifier_litteral  ( method name )   ";
                    temp += vn;
                    container.push(temp);
                    c = c.substr(c.find('('));
                }
                else if (is_intailize(c) == 3)
                {
                    vn = cut(c, ')');
                    temp = "identifier_litteral  ( para name )   ";
                    temp += vn;
                    container.push(temp);
                    c = c.substr(c.find(')'));
                }
                else
                {
                    cout << "error in data type analysis ....\n"; 
                    exit(0); 
                }
                
                continue;
           }

            container.push(keywords[index]);
            c = c.substr(keywords[index].length());

        }
        else
        {
            c = c.substr(1);
        }
       

        



       
       



      
       
    }
    

    return container; 
      

       
   
 
}



int main()
{
    // read file ( input.txt )
     char file_name[25];
      cout << "Enter name of a file you need to read from it : ";
      cin >> file_name;
      string mycode = readfile(file_name);
 
    // proceessing the source code  ( text ) before apply textual analysis on it 
      text_processor(mycode);
   

    // apply textual analysis on it and gathering the tokens in queue 
      queue<string> tokens = get_tokens(mycode);


   // store file ( output.txt ) 
      cout << "Enter name of a file you need to write into it : ";
      cin >> file_name;
      writefile(tokens, file_name); 
     




   

   
    
    
    
    

   


   
    
    system("pause");
    return 0;



}
   
    
