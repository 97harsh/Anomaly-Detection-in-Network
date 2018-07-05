/*
 Network File Converter
  
  Authour:Sharma Harsh
 
 Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License with 
this document.

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.*/

//Please Edit the file so as to find the required feature from the Log
#include<regex>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

const regex hostname("[a-zA-Z0-9_-]+.pune.cdac.in");
const regex typepattern("type=[a-zA-Z0-9_-]+");
const regex subtypep("subtype=[a-zA-Z0-9_-]+");
const regex eventtypep("eventtype=[a-zA-Z0-9_-]+");
const regex srcipp("srcip=[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
const regex dstipp("dstip=[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
const regex dstportp("dstport=[0-9]+");
//const regex srcportp("srcport=[0-9]+");
const regex statusp("status=[a-zA-Z\"]+");
/*datep=re.compile(r'date=\d{4}[-/]\d{2}[-/]\d{2}')
const regex timep("time=[0-9]{2}:[0-9]{2}:[0-9]{2}");
const regex levelp("level=[0-9a-zA-Z_-]+");
const regex attacknamep("attackname=\".*?\"");
const regex srcintfp("srcintf=\"[0-9a-zA-Z_-]+\""); 
const regex dstintfp("dstintf=\"[0-9a-zA-Z_-]+\"");
sessionidp=re.compile(r'sessionid=\d{1,10}');
policyidp=re.compile(r'policyid=\d+')
dstcountryp=re.compile(r'dstcountry="[ \w]+"') #include white spaces w~[a-zA-Z0-9]so [ \w]+ works
srccountryp=re.compile(r'srccountry="[ \w]+"')
trandispp=re.compile(r'trandisp=\w+')
servicep=re.compile(r'service=[/\w-]+')
srcnamep=re.compile(r'srcname=[\w-]+')
durationp=re.compile(r'duration=\d+')
sentbytep=re.compile(r'sentbyte=\d+')
rcvdbytep=re.compile(r'rcvdbyte=\d+')
devtypep=re.compile(r'devtype="[ \w]+"')
osnamep=re.compile(r'osname="[ \w]+"')
osversionp=re.compile(r'osversion="[\w ]+"')
mastersrcmacp=re.compile(r'mastersrcmac=\w{2}:\w{2}:\w{2}:\w{2}:\w{2}:\w{2}')
srcmacp=re.compile(r'srcmac=\w{2}:\w{2}:\w{2}:\w{2}:\w{2}:\w{2}')
crscorep=re.compile(r'crscore=\d+')
cractionp=re.compile(r'craction=\d+')
unauthusersourcep=re.compile(r'unauthusersource="\w+"')
unauthuserp=re.compile(r'unauthuser="[ \w@.-]+"')
vdp=re.compile(r'vd=[\w"]+')
vpntunnelp=re.compile(r'vpntunnel="\w+"')
protop=re.compile(r'proto=\d+')
sentpktp=re.compile(r'sentpkt=\d')
rcvdpktp=re.compile(r'rcvdpkt=\d+')
transipp=re.compile(r'transip=\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}')
transportp=re.compile(r'transport=\d+')
msgp=re.compile(r'msg="[ \w.:,]+"')
rolep=re.compile(r'role=\w+')
appp=re.compile(r'app=["/\w-]+')
applistp=re.compile(r'applist="[\w-]+"')
*/
const regex equality("[a-zA-Z0-9_-]+=");
int regex_searching(string s,vector<regex> r);

int main(int argc, char *argv[])
{
	int i=0;
	
	vector<regex> regvec;
	smatch temp;
	ofstream outfile;
	outfile.open("./heatmaptry1.csv",ios::out);
	//regvec.push_back(hostname);
	regvec.push_back(srcipp);
	regvec.push_back(dstipp);
	regvec.push_back(dstportp);
	regvec.push_back(statusp);
	//regvec.push_back(typepattern);
	//regvec.push_back(subtypep);
	//regvec.push_back(eventtypep);
	//ofstream outfile("./converted.csv");
	while(++i<argc)
	{	
		ifstream infile;
		infile.open(argv[i]);
		//outfile.open("./heatmaptry"+to_string(i-1)+".csv",ios::out);
		cout<<i<<". opening "<<argv[i];
		if(outfile.is_open())
		{
			if(infile.is_open())
			{
				for(string line;getline(infile,line);)
				{
				
					outfile<<(line.substr(0,32))<<","; //writing the time stamp composed of first 32 charecters 
					for(int i=0;i<regvec.size();i++)
					{
						if(!regex_match(line,regvec[i]))
						{

							regex_search(line,temp,regvec[i]);
							outfile<<regex_replace(temp.str(),equality,"")<<",";


						}
						else
							outfile<<",";

					}
					outfile<<"\n";
				
				}
				cout<<" Done!"<<endl;
				infile.close();
			}
			else 
			{
				cout<<"Error opening file "<<argv[i];
				exit(1);
			}
			
				
		}
		else
		{
			cout<<"unable to write to file";
			exit(1);
		}
		//outfile.close();
	}

	outfile.close();
	cout<<"completed";

	return 0;

}
/*int regex_searching(string s,vector<regex> r)
{
	
	
	if(outfile.is_open()) ///file open/close very costly
	{
		outfile<<(s.substr(0,32))<<","; //writing the time stamp composed of first 32 charecters 
		for(int i=0;i<r.size();i++)
		{
			if(!regex_match(s,r[i]))
			{

				regex_search(s,temp,r[i]);
				outfile<<regex_replace(temp.str(),equality,"")<<",";


			}
			else
				outfile<<",";

		}
		outfile<<"\n";
		outfile.close();
	}
	else
	{
		cout<<"unable to write to file";
		exit(1);
	}
	return 0;

}*/
