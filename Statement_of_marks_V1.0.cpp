#include<stdlib.h>
#include<conio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

int studentCount;
char filename[100];
FILE *fp;

struct student
{
	int roll_number;
	string name;
	int marks[6];
	float percentage;
	char grade;
};


class design
{
	public:
		void heading()
		{
			cout<<"\n\t\t\t\t\t";
			for(int i=1;i<=47;i++)
			{
				cout<<"-";
			}
			cout<<"\n\t\t\t\t\t Students Statement OF Marks Generation System\n\t\t\t\t\t";
			for(int i=1;i<=47;i++)
			{
				cout<<"_";
			}
			cout<<"\n";
		}

		void footing()
		{
			cout<<"\n\t\t\t\t\t";
			for(int i=1;i<=47;i++)
			{
				cout<<"_";
			}
			cout<<"\n\t\t\t\t\t";
		}
};

class fileHandling
{
	public:
		int read_saved_data(struct student s[])
		{
			ifstream fin;
			cout<<"Please wait while gather saved data\n";
			string temp;
			int total;
			fin.open("studentdata.bin");
			if(fin.is_open())
			{
				getline(fin,temp);
				for(int i=0;i<studentCount;i++)
				{	
					if(getline(fin,temp,','))
					{
						istringstream convert(temp);
						convert>>s[i].roll_number;
					}
					else
					{
						cout<<"\n"<<"Error : unable To Read roll number at line no."<<i+1;
						getch();
						return 3;
					}
					if(getline(fin,s[i].name,','))
					{
					}
					else
					{
						cout<<"\n"<<"Error : unable To Read student name at line no."<<i+1;
						getch();
						return 3;
					}
						total=0;		
					for(int j=0;j<6;j++)
					{
						if(j<5)
						{
							if(getline(fin,temp,','))
							{
								istringstream convert(temp);
								convert>>s[i].marks[j];
								total+=s[i].marks[j];
							}
							else
							{
								cout<<"\n"<<"Error : unable To Read marks of subject "<<j+1<<" at line no."<<i+1;
								getch();
								return 3;
							}
						}
						else
						{
							if(getline(fin,temp))
							{
								istringstream convert(temp);
								convert>>s[i].marks[j];
								total+=s[i].marks[j];
							}
							else
							{
								cout<<"\n"<<"Error : unable To Read marks of subject "<<j+1<<" at line no."<<i+1;
								getch();
								return 3;
							}
						}
					}
					s[i].percentage=static_cast<float>(total)/6;
					if (s[i].percentage > 90) 
					{
        			    s[i].grade = 'A';
       				}
        			else if (s[i].percentage > 80) 
					{
    			        s[i].grade = 'B';
    			    }
        			else if (s[i].percentage > 60) 
					{
        			    s[i].grade = 'C';
       				}
        			else if (s[i].percentage > 40) 
					{
        			    s[i].grade = 'D';
        			}
        			else if (s[i].percentage >= 35) 
					{
        			    s[i].grade = 'E';
        			}
        			else 
					{
        			    s[i].grade = 'F';
        			}
					
				}
				fin.close();
			}
			else
			{
				cout<<"Error opening Student.bin file";
				return 3;
			}
			cout<<"All data has been gathred successfully"<<"\n"<<"Press Any key to Continue";
		}
		
		
		void write_data(struct student s[],int a)
		{
			ofstream fout;
			fout.open("studentdata.bin");
			if(fout.is_open())
			{
				fout<<studentCount<<"\n";
				for(int i=0;i<studentCount;i++)
				{	
					fout<<s[i].roll_number<<","<<s[i].name<<",";
			
					for(int j=0;j<6;j++)
					{
						fout<<s[i].marks[j];
						if(j<5)
						{
							fout<<",";
						}
						else
						{
							fout<<"\n";
						}
					}
				}
				fout.close();
				cout<<"\n"<<"\n\t\t\t\t\t"<<"All data has been Saved Successfully "<<"\n\n";
				if(a==0)
				{
					cout<<"\n\t\t\t\t\t"<<" You Can close this window"<<"\n\n";
				}
				else
				{
					cout<<"\n\t\t\t\t\t"<<" Press any key to continue ..."<<"\n";
				}
			}
			else
			{
				cout<<"ERROR : Unable to write student data to file";
				return;
			}
		}
		
		void exportMarksheet_file(struct student s[],int i)
		{
			stringstream ss;
			ss<<"Statement_"<<s[i].roll_number<<".txt";
			string filename=ss.str();

			ofstream fout;
			fout.open(filename.c_str());
					for(int j=0;j<80;j++)
					{
						fout<<"=";
					}
					
					fout<<"\n\t\t\tStatement of marks\n";
					
					for(int j=0;j<80;j++)
					{
						fout<<"=";
					}
				
					fout<<"\nStudent Name : "<<s[i].name;
					fout<<"\t\t\tRoll number : "<<s[i].roll_number<<"\n\n";
						
					for(int j=0;j<80;j++)
					{
						fout<<"=";
					}
					
					fout<<"\n";
					
					for(int j=0;j<6;j++)
					{
						fout<<"Subject "<<j+1<<" : "<<s[i].marks[j];
						if(j==2)
						{
							fout<<"\t\t\t\t\t"<<"Percentage : "<<s[i].percentage<<"\n";
						}
						else if(j==3)
						{
							fout<<"\t\t\t\t\t"<<"Grade : "<<s[i].grade<<"\n";
						}	
						else
						{
							cout<<"\n";
						}
						if(j<5)
						{
							for(int k=0;k<80;k++)
							{	
								fout<<"_";
							}
							fout<<"\n";
						}	
					}
					
					for(int j=0;j<80;j++)
					{
						fout<<"=";
					}
					fout.close();
					cout<<"\n\n"<<"Marksheet has been Exported successfully";
		}
};

class dataHandling : public design, public fileHandling
{
	public:
		void receieveData(struct student s[])
		{
			heading();
			int rollNumber,e=studentCount,n,h,a,total;
			cout<<"\n\t\t\t\t\t"<<"Enter number of students to Enter data : ";
			cin>>n;
	
			cout<<"\n\t\t\t\t\t"<<"Enter students details : "<<"\n";
	
		
			for(int i=studentCount;i<(e+n);i++)
			{
				roll: system("cls");
				heading();
				cout<<"\n\t\t\t\t\t"<<"Enter roll number of student "<<(i-e)+1<<" : ";
				cin>>rollNumber;
				fflush(stdin);
				int count=0;
				for(int j=0;j<i;j++)
				{
					if(s[j].roll_number == rollNumber)
					{
						count++;
					}
				}
				if(count>0)
				{
					error: cout<<"\n\t\t\t\t\t"<<"duplicate roll number existed "<<"\n\n\t\t\t\t\t"<<"please enter 1 to try again"<<"\n\n\t\t\t\t\t"<<"or enter any number to go back in main menu : ";
					cin>>h;
					if(h==1)
					{
						goto roll;
					}
					else
					{
						return;
					}
				}
				else
				{
					s[i].roll_number=rollNumber;			
				}
					
				cout<<"\n\n\t\t\t\t\t"<<"Enter name of student "<<(i-e)+1<<"  : ";
				getline(cin,s[i].name);
				fflush(stdin);
				total=0;
				for(int j=0;j<6;j++)
				{
					marks : cout<<"\n\n\t\t\t\t\t"<<"Enter marks of subject "<<j+1<<" (out of 100) : ";
					cin>>a;
					fflush(stdin);
					if((a<=100) && (a>=0))
					{
						s[i].marks[j]=a;
						total+=s[i].marks[j];
					}
					else
					{
						cout<<"\t\t\t\t\t"<<"Error : Please try again & enter marks out of 100";
						goto marks;
					}
				}
				s[i].percentage=static_cast<float>(total)/6;
				if (s[i].percentage > 90) 
				{
        		    s[i].grade = 'A';
       			}
        		else if (s[i].percentage > 80) 
				{
    		        s[i].grade = 'B';
    		    }
        		else if (s[i].percentage > 60) 
				{
        		    s[i].grade = 'C';
       			}
        		else if (s[i].percentage > 40) 
				{
        		    s[i].grade = 'D';
        		}
        		else if (s[i].percentage >= 35) 
				{
        		    s[i].grade = 'E';
        		}
        		else 
				{
        		    s[i].grade = 'F';
        		}
				
				cout<<"\n\n\t\t\t\t\t"<<"Student Data Has been Added successfully"<<"\n\n\t\t\t\t\t"<<"Press Any Key to Continue ....";
				getch();
				studentCount++;
			}
		}
		
		int deleteData(struct student s[])
		{
			heading();
			int index,rollNumber,a,count=0;
			search : cout<<"\n\n\t\t\t\t\t"<<"Enter roll number of student to delete data : ";
			cin>>rollNumber;
			for(int i=0;i<studentCount;i++)
			{
				
				if(s[i].roll_number == rollNumber)
				{
					index=i;
					count++;
					break;
				}
			}
			if(count==0)
			{
				system("cls");
				heading();
				cout<<"\n\n\t\t\t\t\t"<<"No records found for roll number : "<<rollNumber<<"\n\t\t\t\t\t"<<"Enter 0 for Main Menu "<<"\n\t\t\t\t\t"<<"Enter any number to try again : ";
				cin>>a;
				if(a==0)
				{
					return 2;
				}
				goto search;	
			}	
			for(int i=index;i<(studentCount-1);i++)
			{
				s[i]=s[i+1];
			}
			studentCount--;
			cout<<"\n\t\t\t\t\t"<<"Data Has Been deleted successfully"<<"\n\t\t\t\t\t"<<"Press Any key to continue";
			return 0;
		}
		
	public:
		void updateData(struct student s[])
		{
			heading();
			int a,b,h,rollNumber,total,cnt=0;
			search:	
					cout<<"\n\n\t\t\t\t"<<"Enter Roll number of student to Update student data : ";
					cin>>a;
			
					for(int i=0;i<studentCount;i++)	
					{
						if(a==s[i].roll_number)
						{
							roll: system("cls");
							heading();
							cout<<"\n\t\t\t\t\t"<<"Enter new roll number of student "<<s[i].name<<" : ";
							if(!(cin>>rollNumber))
							{
								fflush(stdin);
								cin.clear();
								cout<<"\n\t\t\t\t\t"<<"Error : Invalid Input Please Try again"<<"\n";
								goto roll;
							}
							fflush(stdin);
							int count=0;
							for(int j=0;j<i;j++)
							{
								if(s[j].roll_number == rollNumber)
								{
									count++;
								}
							}
							if(count>0)
							{
								cout<<"\n\n\t\t\t\t\t"<<"duplicate roll number existed "<<"\n\n\t\t\t\t\t"<<"please enter 1 to try again"<<"\n\n\t\t\t\t\t"<<"or enter any number to go back in main menu : ";
								cin>>h;
								if(h==1)
								{
									goto roll;
								}
								else
								{
									return;
								}
							}
							else
							{
								s[i].roll_number=rollNumber;			
							}
		
							cout<<"\n\n\n\t\t\t\t\t"<<"Enter new name of student : ";
							getline(cin,s[i].name);
							fflush(stdin);
							total=0;
							for(int j=0;j<6;j++)
							{
								marks : cout<<"\n\n\t\t\t\t\t"<<"Enter new marks of subject "<<j+1<<" : ";
								cin>>b;
								fflush(stdin);
								if((b<=100) && (b>=0))
								{
									s[i].marks[j]=b;
									total+=s[i].marks[j];
								}
								else
								{
									cout<<"\t\t\t\t\t"<<"Error : Please try again & enter marks out of 100";
									goto marks;
								}
								
							}
							s[i].percentage=static_cast<float>(total)/6;
							if (s[i].percentage > 90) 
							{
        			    		s[i].grade = 'A';
       						}
        					else if (s[i].percentage > 80) 
							{
    			    		    s[i].grade = 'B';
    			    		}
        					else if (s[i].percentage > 60) 
							{
        					    s[i].grade = 'C';
       						}
        					else if (s[i].percentage > 40) 
							{
        			    		s[i].grade = 'D';
        					}
        					else if (s[i].percentage >= 35) 
							{
        					    s[i].grade = 'E';
        					}
        					else 
							{
        					    s[i].grade = 'F';
        					}
							cnt++;
							cout<<"\n\n\t\t\t\t\t"<<"Data Has Been Updated Successfully"<<"\n\n\t\t\t\t\t"<<"Press Any Key to Continue  .....";
							break;
						}
					}
					if(cnt==0)
					{
						cout<<"\n\n\t\t\t\t"<<"No Data Found for the roll number "<<a<<"\n\t\t\t\t"<<"Press Any Key to Continue .....";
					}	
		}
	public:
		void printMarksheet(struct student s[])
		{
			heading();
			int count,a,b,c;
			search:	
					cout<<"\n\n\t\t\t\t"<<"Enter Roll number of student to Generate statement of marks : ";
					cin>>a;
			
				for(int i=0;i<studentCount;i++)
				{
					count=0;
					if(a==s[i].roll_number)
					{
						system("cls");
						cout<<"\n";
						for(int j=0;j<80;j++)
						{
							cout<<"=";
						}
				
						cout<<"\n\t\t\t"<<"Statement of marks"<<"\n";
				
						for(int j=0;j<80;j++)
						{
							cout<<"=";
						}
				
						cout<<"\n"<<"Student Name : "<<s[i].name;
						cout<<"\t\t\t"<<"Roll number : "<<s[i].roll_number<<"\n\n";
				
						for(int j=0;j<80;j++)
						{
							cout<<"=";
						}
				
						cout<<"\n";
				
						for(int j=0;j<6;j++)
						{
							cout<<"Subject "<<j+1<<" : "<<s[i].marks[j];
							if(j==2)
							{
								cout<<"\t\t\t\t\t"<<"Percentage : "<<s[i].percentage<<"\n";
							}
							else if(j==3)
							{
								cout<<"\t\t\t\t\t"<<"Grade : "<<s[i].grade<<"\n";
							}
							else
							{
								cout<<"\n";
							}
							if(j<5)
							{
								for(int k=0;k<80;k++)
								{
									cout<<"_";
								}
								cout<<"\n";
							}	
						}	
				
						for(int j=0;j<80;j++)
						{
							printf("=");
						}
						cout<<"\n\n"<<"Enter 1 to Export this marksheet to a file "<<"\n"<<"Or enter any number to continue :  ";
						cin>>b;
						if(b==1)
						{
							exportMarksheet_file(s,i);
							cout<<"\n\n"<<"Press any key to continue ";
							getch();
						}
						
						count++;
						break;
								
					}
				}
				if(count==0)
				{
					system("cls");
					heading();
					cout<<"\n\n\t\t\t\t\t"<<"No records found for roll number : "<<a<<" \n\t\t\t\t\t"<<"Press any key to try again";
					getch();
				}
		
				error:	system("cls");
				heading();
				cout<<"\n\n\t\t\t\t"<<"Enter 1 to generate another statement & 0 for main menu  :  ";
				cin>>b;
				if(b==1)
				{
					goto search;
				}
		
				else if(b==0)
				{
					return;
				}
				else
				{
					system("cls");
					heading();
					cout<<"\n\t\t\t\t\t"<<"Invalid input : Please press any key to try again";
					footing();
					getch();
					goto error;
				}
		}
};

int main()
{
	dataHandling handler;
	ifstream fin;
	fin.open("studentdata.bin");
	if(fin.is_open())
	{
		int a=fin.get();
		if(a==EOF)
		{
			studentCount=0;
		}
		else
		{
			if(fin.seekg(0,std::ios::beg))
			{
				fin>>studentCount;
			}
			else
			{
				cout<<"Error in Moving file pointer";
				return 3;
			}
		}
		fin.close();
	}
	else
	{
		cout<<"ERROR : Unable to read student count from file";
		return 3;
	}
	int a,studCount=studentCount+500;
	struct student s[studCount];
	if(handler.read_saved_data(s)==3)
	{
		cout<<"Data Reading is UnSuccessfull";
	}
	getch();
	
	main:	system("cls");
	handler.heading();
	cout<<"\n\t\t\t\t\t"<<"  Enter appropriate number for choice "<<"\n\n\t\t\t\t\t"<<"  1   for Enter New Student's Details and Marks"<<"\n\n\t\t\t\t\t"<<"  2   For Generate Statement of marks"<<"\n\n\t\t\t\t\t"<<"  3   For Update Student Data"<<"\n\n\t\t\t\t\t"<<"  4   For Delete Student Data"<<"\n\n\t\t\t\t\t"<<"  5   For Save Updated Data To File"<<"\n\n\t\t\t\t\t"<<"  0   for Save Data & Exit Program";
			handler.footing();
			cin>>a;
			
			
			switch (a)
			{
				case 1 :	system("cls");
							handler.receieveData(s);
							goto main;
				break;
				case 2 :	system("cls");
							handler.printMarksheet(s);
							goto main;
				break;
				case 3 :	system("cls");
							handler.updateData(s);
							getch();
							goto main;
				break;
				case 4 :	system("cls");
							if(handler.deleteData(s)==0)
							{
								getch();	
							}
							goto main;
				break;
				case 5 :	system("cls");
							handler.heading();
							handler.write_data(s,a);
							handler.footing();
							getch();
							goto main;
				break;
				case 0 :	system("cls");
							handler.heading();
							handler.write_data(s,a);
							handler.footing();
							cout<<"\n\n\n\n\n";
							return 0;
				break;
				default :	system("cls");
							cout<<"\n"<<"Invalid input : Please press any key to try again";
							getch();
							goto main;
				break;
			}

}
