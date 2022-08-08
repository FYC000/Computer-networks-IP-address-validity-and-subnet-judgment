#include<iostream>
#include<vector>
#include<string>
using namespace std;

//全局变量 
vector<int>M_data(4,0);//储存掩码地址的矢量 
vector<int>A_data(4,0);//储存AIP地址的矢量 
vector<int>B_data(4,0);//储存BIP地址的矢量 
vector<int>Type(5,0);//用于判断IP地址的种类 
vector<int>ar_data(4,0);//用于存储网络地址的矢量 

//调用函数 

//将整个IP地址转换为用数组储存的整数形式 
void IPToArr(string&IP,vector<int>&data);
//将字符串转换为整数
int StrToNum(string&str,int i,int j); 
//判断IP地址的合法性 
bool CheckIPValid(vector<int>&data); 
//判断掩码地址的合法性 
bool CheckMaValid(vector<int>&data,int cnt);
//判断地址是否有三个'.' 
bool SignValid(string IP);
////判断地址首先有没有三个'.'，如果有,在判断'.'是否相邻,还有开头和结尾是否有'.' 
bool FormCorrect(string IP);
//判断地址数字部分以及字符和数字的位置是否合法 
bool NumberCorrect(string IP);
//判断两个地址是否属于同一个地址以及地址范围是否正确
bool AddressSaType(vector<int>&data1,vector<int>&data2,vector<int>&data); 
//判断两个IP地址是否属于同一个子网络
bool SameNet(vector<int>&M_data,vector<int>&A_data,vector<int>&B_data,int cnt);
//判断IP地址的类型 
void AddressType(vector<int>&data);
//子网划分的个数判断 
int SubnetNumber(int number);
//打印子网划分后的地址 
void SubnetPrintf(vector<int>&data,int cnt,char type);

int main(){
	int cnt,sign=0;//用于存储掩码位数 
	char decide;//用于判断YES OR NO 
	bool left=true,right=true,voucher=false;//left表示判断格式是否正确，right表示数字部分是否正确，voucher判断掩码地址和IP地址是否输入 
	string mask,IP_addA,IP_addB;//用于输入掩码地址和两个IP地址 
	string address1;//用于输入已知地址块的IP地址 
	char type;
	while(true){
		cout<<endl;
		cout<<"####欢迎使用IP地址合法性以及子网判断系统####"<<endl; 
		cout<<"######以下本系统功能######"<<endl;
		cout<<"######1.输入掩码地址和IP地址######"<<endl;
		cout<<"######2.查询两个IP地址是否在同一个网络######"<<endl;
		cout<<"######3.查询IP地址的类型######"<<endl;
		cout<<"######4.子网划分位数######"<<endl;
		cout<<"######5.离开######"<<endl;
		cout<<"######请输入选项(1,2,3,4,5)######"<<endl;
		
		int option;
		do{
			cin>>option;
			if(option!=1&&option!=2&&option!=3&&option!=4&&option!=5){
				cout<<"选择错误，该选项不存在，请重新选择选项！"<<endl; 
			}else break;
		}while(true);//判断选项是否选择错误 
		
		switch(option){
			case 1:
				cout<<"请输入掩码位数,"<<endl;
				do{
					cin>>cnt;
					if(cnt>32||cnt<=0)cout<<"输入掩码位数错误，请重新输入！"<<endl;
				}while(cnt>32||cnt<=0);//判断掩码位数是否输入错误 
				
				cout<<"请输入所在的子网掩码。"<<endl; 
				do{
					cin>>mask;
					IPToArr(mask,M_data);//用int型数组形式存储IP地址
					left=true;
					right=true;
					if(!NumberCorrect(mask)){//用于判断掩码地址的格式合法性
						cout<<"请重新输入子网掩码。"<<endl;
						left=false;
					}else if(!CheckMaValid(M_data,cnt)){//用于判断掩码地址的数字范围合法性
						cout<<"请重新输入子网掩码地址"<<endl;
						right=false;
					}
				}while(!left||!right); 
				cout<<"输入成功"<<endl;
				cout<<endl;
				
				cout<<"请输入A的IP地址"<<endl;
				do{
					cin>>IP_addA;
					IPToArr(IP_addA,A_data);//用int型数组形式存储IP地址
					left=true;
					right=true;
					if(!NumberCorrect(IP_addA)){//用于判断A的IP地址的格式合法性 
						cout<<"请重新输入A的IP地址。"<<endl;
						left=false;
					}else if(!CheckIPValid(A_data)){//用于判断A的IP地址的数字范围合法性 
						cout<<"请重新输入A的IP地址。"<<endl;
						right=false;
					}
				}while(!left||!right);
				cout<<"输入成功"<<endl;	
				cout<<endl;
				
				cout<<"请输入B的IP地址"<<endl;
				do{
					cin>>IP_addB;
					IPToArr(IP_addB,B_data);//用int型数组形式存储IP地址
					left=true;
					right=true;
					if(!NumberCorrect(IP_addB)){//用于判断B的IP地址的格式合法性 
						cout<<"请重新输入B的IP地址。"<<endl;
						left=false;
					}
					else if(!CheckIPValid(B_data)){//用于判断B的IP地址的数字范围合法性 
						cout<<"请重新输入B的IP地址。"<<endl;
						right=false;
					}
				}while(!left||!right);
				cout<<"输入成功"<<endl;
				voucher=true;
				break;
			
			case 2:
				if(!voucher){
					cout<<"掩码地址或IP地址数据缺失，无法执行该功能！请重新输入地址数据。"<<endl;
					break;
				}
				if(!AddressSaType(A_data,B_data,Type)){//先判断两个IP地址的类型是否一样 
					cout<<"两个IP地址不属于同一个子网络"<<endl;
				}else if(SameNet(M_data,A_data,B_data,cnt))cout<<"两个IP地址属于同一个子网络"<<endl;//然后判断两个IP地址是否在同一个子网掩码下 
				else cout<<"两个IP地址不属于同一个子网络"<<endl;
				break;
				
			case 3:
				if(!voucher){
					cout<<"掩码地址或IP地址数据缺失，无法执行该功能！请重新输入地址数据。"<<endl;
					break;
				}
				if(!AddressSaType(A_data,B_data,Type)){//先判断两个IP地址的类型是否一样 
					cout<<"由于两个IP地址的类型不一样，重新从选项1开始输入IP地址"<<endl;
					break;
				}else if(!SameNet(M_data,A_data,B_data,cnt)){
					cout<<"两个IP地址不属于同一个子网络,请重新从选项1开始输入IP地址"<<endl;
					break;
				}
				cout<<"是否查询IP地址类型?(Y,y(判断地址类型) or N,n(返回上一级))"<<endl;
				do{
					cin>>decide;
					if(!(decide=='Y'||decide=='y'||decide=='N'||decide=='n')){
						cout<<"输入错误，请重新输入！"<<endl;
					}
					if(decide=='Y'||decide=='y')AddressType(Type);//用于判断IP地址的类型 
				}while(!(decide=='Y'||decide=='y'||decide=='N'||decide=='n'));
				break;
			case 4:
				int number,cnt;
				do{
					cout<<"请填入划分子网的个数"<<endl;
					cin>>cnt;
					if(SubnetNumber(cnt)==-1){
						cout<<"划分位数溢出，划分失败，请重新输入数据" <<endl;
					}
					else{
						number=SubnetNumber(cnt);
						if(number<8)
						break;
					}
				}while(true);
				cout<<"网络地址的种类(A，B，C)"<<endl;
				cin>>type;
				cout<<"请输入你的网络地址"<<endl;
				do{
					cin>>address1;
					IPToArr(address1,ar_data);//用int型数组形式存储IP地址
					left=true;
					right=true;
					if(!NumberCorrect(address1)){//用于判断网络地址的格式合法性 
						cout<<"请重新输入网络地址。"<<endl;
						left=false;
					}else if(!CheckIPValid(ar_data)){//用于判断网络地址的数字范围合法性 
						cout<<"请重新输入网络地址。"<<endl;
						right=false;
					}
				}while(!left||!right);
				cout<<"输入成功"<<endl;	
				cout<<endl;
				SubnetPrintf(ar_data,number,type);//打印网络地址的子网划分 
				break;
			
			case 5:
				cout<<"是否确认退出本系统？(Y,y(退出该系统) or N,n(返回上一级))"<<endl;
				do{
					cin>>decide;
					if(!(decide=='Y'||decide=='y'||decide=='N'||decide=='n')){
						cout<<"输入错误，请重新输入！"<<endl;
					}
					if(decide=='Y'||decide=='y'){
						cout<<"即将结束应用系统"<<endl;
						return 0;
					}
				}while(!(decide=='Y'||decide=='y'||decide=='N'||decide=='n'));
				break;	
					
		}	
	}	
}

void IPToArr(string&IP,vector<int>&data){  //将整个IP地址转换为用数组储存的整数形式 
	int index=0;
	int i=0;
	for(int j=0;j<IP.length()+1;j++)
		if((j==IP.length())||(IP[j]=='.')){
			data[index++]=StrToNum(IP,i,j);
			i=j+1;
		}	
}

int StrToNum(string&str,int i,int j){ //将字符串转换为整数 
	int ret=0;
	while(i<j){
		ret=ret*10+str[i]-'0';
		i++;
	}
	return ret;
}

bool CheckIPValid(vector<int>&data){  //判断IP地址的合法性 
	for(int i=0;i<data.size();i++)
		if(data[i]>255||data[i]<0){
			cout<<"数字部分存在大于255或者小于0,";
			return false;
		}	
	return true;
}

bool CheckMaValid(vector<int>&data,int cnt){//判断掩码地址的合法性 
	int add[8]={128,192,224,240,248,252,254,255};
	for(int i=0;i<data.size();i++){
		if((cnt-1)/8==i){//判断不满足255时掩码地址中一部分是否正确，cnt-1防止出现16/8=2的情况 
			if(data[i]!=add[(cnt-1)%8]){
				cout<<"掩码地址中小于255的部分数字出现问题,";
				return false;
			}
		}
		else if((cnt-1)/8>i){//掩码地址中前面几位是否等于255 
			if(data[i]!=255){
				cout<<"掩码地址等于255的数字部分不等于255，";
				return false;
			}
		}else {//用于判断大于掩码地址位数后数字是否还为0 
			if(data[i]!=0){
				cout<<"掩码地址中为0部分的数字不为0，";
				return false;
			}
		}
	}
	return true;
}

bool SignValid(string IP){//判断地址是否有三个'.' 
	int cnt=0;
	for(int i=0;i<IP.length()+1;i++){
		if(IP[i]=='.')cnt++;
	}
	if(cnt==3)return true;
	cout<<"IP地址中不存在只有三个字符'.'的情况，所以格式错误，";
	return false;
}

bool FormCorrect(string IP){//判断地址首先有没有三个'.'，如果有,在判断'.'是否相邻,还有开头和结尾是否有'.' 
	if(!SignValid(IP))return false;
	int i;
	for(i=0;i<IP.length()+1;i++){
		if(IP[i]=='.'&&IP[i+1]=='.'){
			cout<<"IP地址存在相邻字符'.'，格式错误,";
			return false;
		}
	}
	if(IP[i-2]=='.'){
		cout<<"结尾有字符'.'，格式错误，";
		return false;
	}
	if(IP[0]=='.'){
		cout<<"开头有字符'.',格式错误，";
		return false;
	} 
	return true;
}

bool NumberCorrect(string IP){//判断地址数字部分位数是否不大于3位以及字符'.'的格式是否正确 
	if(!FormCorrect(IP))return false;
	int j=0;
	bool flag=true;
	for(int i=0;i<IP.length()+1;i++){
		if(IP[i]=='.'){
			for(int k=j;k<=i&&k<j+4;k++){
				if(IP[k]=='.'){
					j=i+1;
					flag=true;
					break;
				}
				flag=false;
			}
			if(!flag){
				cout<<"每四位字符中没有出现字符'.'，所以格式错误,";
				return false; 
			}
		}
	}
	return true;
}

bool AddressSaType(vector<int>&data1,vector<int>&data2,vector<int>&data){//判断两个地址是否属于同一个地址以及地址范围是否正确 
	if((data1[0]>=1&&data1[0]<=127&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=1&&data2[0]<=126&&data2[3]>=0&&data2[3]<=255)){//判断两个地址是否都为A类地址 
		data[0]=1;
		return true;  
	} 
	else if((data1[0]>=128&&data1[0]<=191&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=128&&data2[0]<=191&&data2[3]>=0&&data2[3]<=255)){//判断两个地址是否都为B类地址 
		data[1]=1;
		return true;
	}
	else if((data1[0]>=192&&data1[0]<=223&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=192&&data2[0]<=223&&data2[3]>=0&&data2[3]<=255)){//判断两个地址是否都为C类地址 
		data[2]=1;
		return true;
	}
	else if((data1[0]>=224&&data1[0]<=239&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=224&&data2[0]<=239&&data2[3]>=0&&data2[3]<=255)){//判断两个地址是否都为D类地址 
		data[3]=1;
		return true;
	}
	else if((data1[0]>=240&&data1[0]<=255&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=240&&data2[0]<=255&&data2[3]>=0&&data2[3]<=255)){//判断两个地址是否都为E类地址 
		data[4]=1;
		return true;
	}
	return false;
}

bool SameNet(vector<int>&M_data,vector<int>&A_data,vector<int>&B_data,int cnt){//判断两个IP地址是否属于同一个子网络 
	if(CheckMaValid(M_data,cnt)&&CheckIPValid(A_data)&&CheckIPValid(B_data)){ 
		for(int i=0;i<M_data.size();i++){
			if((M_data[i]&A_data[i])!=(M_data[i]&B_data[i])) {
				return false;
			}
		}
		return true;
	}else return false;
} 

void AddressType(vector<int>&data){//判断IP地址的类型 
	char ag[5]={'A','B','C','D','E'};
	for(int i=0;i<5;i++){
		if(data[i]) cout<<"地址类型为" <<ag[i]<<"类地址"<<endl;
	}
}

int SubnetNumber(int number){//子网划分的个数判断 
	int redouble[8]={1,2,4,8,16,32,64,128};
	for(int i=0;i<8;i++){
		if(number==1)return 0;
		if(number>redouble[i]&&number<=redouble[i+1]){
			return i+1;
		}
	}
	return -1;
}

void SubnetPrintf(vector<int>&data,int cnt,char type){//打印子网划分后的地址 
	int number[9]={0,128,64,32,16,8,4,2,1}; 
	int redouble[8]={1,2,4,8,16,32,64,128};
	switch(type){
		case 'A': 
			cout<<"A地址的子网划分范围为："<<endl;
			for(int i=0;i<redouble[cnt];i++){
				if(i==0){
					for(int k=0;k<4;k++){
						if(k!=3){
							cout<<data[k]<<'.';
						}
						else cout<<data[k]<<endl;
					}
				}
				else{
					data[1]+=number[cnt];
					for(int k=0;k<4;k++){
						if(k!=3){
							cout<<data[k]<<'.';
						}
						else cout<<data[k]<<endl;
					}
				}
			}
			break;
		case 'B':
			cout<<"B地址的子网划分范围为："<<endl;
			for(int i=0;i<redouble[cnt];i++){
				if(i==0){
					for(int k=0;k<4;k++){
						if(k!=3){
							cout<<data[k]<<'.';
						}
						else cout<<data[k]<<endl;
					}
				}
				else{
					data[2]+=number[cnt];
					for(int k=0;k<4;k++){
						if(k!=3){
							cout<<data[k]<<'.';
						}
						else cout<<data[k]<<endl;
					}
				}
			}
			break;
		case 'C':
			cout<<"C地址的子网划分范围为："<<endl;
			for(int i=0;i<redouble[cnt];i++){
				if(i==0){
					for(int k=0;k<4;k++){
						if(k!=3){
							cout<<data[k]<<'.';
						}
						else cout<<data[k]<<endl;
					}
				}
				else{
					data[3]+=number[cnt];
					for(int k=0;k<4;k++){
						if(k!=3){
							cout<<data[k]<<'.';
						}
						else cout<<data[k]<<endl;
					}
				}
			}
			break;
	}
}
