#include<iostream>
#include<vector>
#include<string>
using namespace std;

//ȫ�ֱ��� 
vector<int>M_data(4,0);//���������ַ��ʸ�� 
vector<int>A_data(4,0);//����AIP��ַ��ʸ�� 
vector<int>B_data(4,0);//����BIP��ַ��ʸ�� 
vector<int>Type(5,0);//�����ж�IP��ַ������ 
vector<int>ar_data(4,0);//���ڴ洢�����ַ��ʸ�� 

//���ú��� 

//������IP��ַת��Ϊ�����鴢���������ʽ 
void IPToArr(string&IP,vector<int>&data);
//���ַ���ת��Ϊ����
int StrToNum(string&str,int i,int j); 
//�ж�IP��ַ�ĺϷ��� 
bool CheckIPValid(vector<int>&data); 
//�ж������ַ�ĺϷ��� 
bool CheckMaValid(vector<int>&data,int cnt);
//�жϵ�ַ�Ƿ�������'.' 
bool SignValid(string IP);
////�жϵ�ַ������û������'.'�������,���ж�'.'�Ƿ�����,���п�ͷ�ͽ�β�Ƿ���'.' 
bool FormCorrect(string IP);
//�жϵ�ַ���ֲ����Լ��ַ������ֵ�λ���Ƿ�Ϸ� 
bool NumberCorrect(string IP);
//�ж�������ַ�Ƿ�����ͬһ����ַ�Լ���ַ��Χ�Ƿ���ȷ
bool AddressSaType(vector<int>&data1,vector<int>&data2,vector<int>&data); 
//�ж�����IP��ַ�Ƿ�����ͬһ��������
bool SameNet(vector<int>&M_data,vector<int>&A_data,vector<int>&B_data,int cnt);
//�ж�IP��ַ������ 
void AddressType(vector<int>&data);
//�������ֵĸ����ж� 
int SubnetNumber(int number);
//��ӡ�������ֺ�ĵ�ַ 
void SubnetPrintf(vector<int>&data,int cnt,char type);

int main(){
	int cnt,sign=0;//���ڴ洢����λ�� 
	char decide;//�����ж�YES OR NO 
	bool left=true,right=true,voucher=false;//left��ʾ�жϸ�ʽ�Ƿ���ȷ��right��ʾ���ֲ����Ƿ���ȷ��voucher�ж������ַ��IP��ַ�Ƿ����� 
	string mask,IP_addA,IP_addB;//�������������ַ������IP��ַ 
	string address1;//����������֪��ַ���IP��ַ 
	char type;
	while(true){
		cout<<endl;
		cout<<"####��ӭʹ��IP��ַ�Ϸ����Լ������ж�ϵͳ####"<<endl; 
		cout<<"######���±�ϵͳ����######"<<endl;
		cout<<"######1.���������ַ��IP��ַ######"<<endl;
		cout<<"######2.��ѯ����IP��ַ�Ƿ���ͬһ������######"<<endl;
		cout<<"######3.��ѯIP��ַ������######"<<endl;
		cout<<"######4.��������λ��######"<<endl;
		cout<<"######5.�뿪######"<<endl;
		cout<<"######������ѡ��(1,2,3,4,5)######"<<endl;
		
		int option;
		do{
			cin>>option;
			if(option!=1&&option!=2&&option!=3&&option!=4&&option!=5){
				cout<<"ѡ����󣬸�ѡ����ڣ�������ѡ��ѡ�"<<endl; 
			}else break;
		}while(true);//�ж�ѡ���Ƿ�ѡ����� 
		
		switch(option){
			case 1:
				cout<<"����������λ��,"<<endl;
				do{
					cin>>cnt;
					if(cnt>32||cnt<=0)cout<<"��������λ���������������룡"<<endl;
				}while(cnt>32||cnt<=0);//�ж�����λ���Ƿ�������� 
				
				cout<<"���������ڵ��������롣"<<endl; 
				do{
					cin>>mask;
					IPToArr(mask,M_data);//��int��������ʽ�洢IP��ַ
					left=true;
					right=true;
					if(!NumberCorrect(mask)){//�����ж������ַ�ĸ�ʽ�Ϸ���
						cout<<"�����������������롣"<<endl;
						left=false;
					}else if(!CheckMaValid(M_data,cnt)){//�����ж������ַ�����ַ�Χ�Ϸ���
						cout<<"�������������������ַ"<<endl;
						right=false;
					}
				}while(!left||!right); 
				cout<<"����ɹ�"<<endl;
				cout<<endl;
				
				cout<<"������A��IP��ַ"<<endl;
				do{
					cin>>IP_addA;
					IPToArr(IP_addA,A_data);//��int��������ʽ�洢IP��ַ
					left=true;
					right=true;
					if(!NumberCorrect(IP_addA)){//�����ж�A��IP��ַ�ĸ�ʽ�Ϸ��� 
						cout<<"����������A��IP��ַ��"<<endl;
						left=false;
					}else if(!CheckIPValid(A_data)){//�����ж�A��IP��ַ�����ַ�Χ�Ϸ��� 
						cout<<"����������A��IP��ַ��"<<endl;
						right=false;
					}
				}while(!left||!right);
				cout<<"����ɹ�"<<endl;	
				cout<<endl;
				
				cout<<"������B��IP��ַ"<<endl;
				do{
					cin>>IP_addB;
					IPToArr(IP_addB,B_data);//��int��������ʽ�洢IP��ַ
					left=true;
					right=true;
					if(!NumberCorrect(IP_addB)){//�����ж�B��IP��ַ�ĸ�ʽ�Ϸ��� 
						cout<<"����������B��IP��ַ��"<<endl;
						left=false;
					}
					else if(!CheckIPValid(B_data)){//�����ж�B��IP��ַ�����ַ�Χ�Ϸ��� 
						cout<<"����������B��IP��ַ��"<<endl;
						right=false;
					}
				}while(!left||!right);
				cout<<"����ɹ�"<<endl;
				voucher=true;
				break;
			
			case 2:
				if(!voucher){
					cout<<"�����ַ��IP��ַ����ȱʧ���޷�ִ�иù��ܣ������������ַ���ݡ�"<<endl;
					break;
				}
				if(!AddressSaType(A_data,B_data,Type)){//���ж�����IP��ַ�������Ƿ�һ�� 
					cout<<"����IP��ַ������ͬһ��������"<<endl;
				}else if(SameNet(M_data,A_data,B_data,cnt))cout<<"����IP��ַ����ͬһ��������"<<endl;//Ȼ���ж�����IP��ַ�Ƿ���ͬһ������������ 
				else cout<<"����IP��ַ������ͬһ��������"<<endl;
				break;
				
			case 3:
				if(!voucher){
					cout<<"�����ַ��IP��ַ����ȱʧ���޷�ִ�иù��ܣ������������ַ���ݡ�"<<endl;
					break;
				}
				if(!AddressSaType(A_data,B_data,Type)){//���ж�����IP��ַ�������Ƿ�һ�� 
					cout<<"��������IP��ַ�����Ͳ�һ�������´�ѡ��1��ʼ����IP��ַ"<<endl;
					break;
				}else if(!SameNet(M_data,A_data,B_data,cnt)){
					cout<<"����IP��ַ������ͬһ��������,�����´�ѡ��1��ʼ����IP��ַ"<<endl;
					break;
				}
				cout<<"�Ƿ��ѯIP��ַ����?(Y,y(�жϵ�ַ����) or N,n(������һ��))"<<endl;
				do{
					cin>>decide;
					if(!(decide=='Y'||decide=='y'||decide=='N'||decide=='n')){
						cout<<"����������������룡"<<endl;
					}
					if(decide=='Y'||decide=='y')AddressType(Type);//�����ж�IP��ַ������ 
				}while(!(decide=='Y'||decide=='y'||decide=='N'||decide=='n'));
				break;
			case 4:
				int number,cnt;
				do{
					cout<<"�����뻮�������ĸ���"<<endl;
					cin>>cnt;
					if(SubnetNumber(cnt)==-1){
						cout<<"����λ�����������ʧ�ܣ���������������" <<endl;
					}
					else{
						number=SubnetNumber(cnt);
						if(number<8)
						break;
					}
				}while(true);
				cout<<"�����ַ������(A��B��C)"<<endl;
				cin>>type;
				cout<<"��������������ַ"<<endl;
				do{
					cin>>address1;
					IPToArr(address1,ar_data);//��int��������ʽ�洢IP��ַ
					left=true;
					right=true;
					if(!NumberCorrect(address1)){//�����ж������ַ�ĸ�ʽ�Ϸ��� 
						cout<<"���������������ַ��"<<endl;
						left=false;
					}else if(!CheckIPValid(ar_data)){//�����ж������ַ�����ַ�Χ�Ϸ��� 
						cout<<"���������������ַ��"<<endl;
						right=false;
					}
				}while(!left||!right);
				cout<<"����ɹ�"<<endl;	
				cout<<endl;
				SubnetPrintf(ar_data,number,type);//��ӡ�����ַ���������� 
				break;
			
			case 5:
				cout<<"�Ƿ�ȷ���˳���ϵͳ��(Y,y(�˳���ϵͳ) or N,n(������һ��))"<<endl;
				do{
					cin>>decide;
					if(!(decide=='Y'||decide=='y'||decide=='N'||decide=='n')){
						cout<<"����������������룡"<<endl;
					}
					if(decide=='Y'||decide=='y'){
						cout<<"��������Ӧ��ϵͳ"<<endl;
						return 0;
					}
				}while(!(decide=='Y'||decide=='y'||decide=='N'||decide=='n'));
				break;	
					
		}	
	}	
}

void IPToArr(string&IP,vector<int>&data){  //������IP��ַת��Ϊ�����鴢���������ʽ 
	int index=0;
	int i=0;
	for(int j=0;j<IP.length()+1;j++)
		if((j==IP.length())||(IP[j]=='.')){
			data[index++]=StrToNum(IP,i,j);
			i=j+1;
		}	
}

int StrToNum(string&str,int i,int j){ //���ַ���ת��Ϊ���� 
	int ret=0;
	while(i<j){
		ret=ret*10+str[i]-'0';
		i++;
	}
	return ret;
}

bool CheckIPValid(vector<int>&data){  //�ж�IP��ַ�ĺϷ��� 
	for(int i=0;i<data.size();i++)
		if(data[i]>255||data[i]<0){
			cout<<"���ֲ��ִ��ڴ���255����С��0,";
			return false;
		}	
	return true;
}

bool CheckMaValid(vector<int>&data,int cnt){//�ж������ַ�ĺϷ��� 
	int add[8]={128,192,224,240,248,252,254,255};
	for(int i=0;i<data.size();i++){
		if((cnt-1)/8==i){//�жϲ�����255ʱ�����ַ��һ�����Ƿ���ȷ��cnt-1��ֹ����16/8=2����� 
			if(data[i]!=add[(cnt-1)%8]){
				cout<<"�����ַ��С��255�Ĳ������ֳ�������,";
				return false;
			}
		}
		else if((cnt-1)/8>i){//�����ַ��ǰ�漸λ�Ƿ����255 
			if(data[i]!=255){
				cout<<"�����ַ����255�����ֲ��ֲ�����255��";
				return false;
			}
		}else {//�����жϴ��������ַλ���������Ƿ�Ϊ0 
			if(data[i]!=0){
				cout<<"�����ַ��Ϊ0���ֵ����ֲ�Ϊ0��";
				return false;
			}
		}
	}
	return true;
}

bool SignValid(string IP){//�жϵ�ַ�Ƿ�������'.' 
	int cnt=0;
	for(int i=0;i<IP.length()+1;i++){
		if(IP[i]=='.')cnt++;
	}
	if(cnt==3)return true;
	cout<<"IP��ַ�в�����ֻ�������ַ�'.'����������Ը�ʽ����";
	return false;
}

bool FormCorrect(string IP){//�жϵ�ַ������û������'.'�������,���ж�'.'�Ƿ�����,���п�ͷ�ͽ�β�Ƿ���'.' 
	if(!SignValid(IP))return false;
	int i;
	for(i=0;i<IP.length()+1;i++){
		if(IP[i]=='.'&&IP[i+1]=='.'){
			cout<<"IP��ַ���������ַ�'.'����ʽ����,";
			return false;
		}
	}
	if(IP[i-2]=='.'){
		cout<<"��β���ַ�'.'����ʽ����";
		return false;
	}
	if(IP[0]=='.'){
		cout<<"��ͷ���ַ�'.',��ʽ����";
		return false;
	} 
	return true;
}

bool NumberCorrect(string IP){//�жϵ�ַ���ֲ���λ���Ƿ񲻴���3λ�Լ��ַ�'.'�ĸ�ʽ�Ƿ���ȷ 
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
				cout<<"ÿ��λ�ַ���û�г����ַ�'.'�����Ը�ʽ����,";
				return false; 
			}
		}
	}
	return true;
}

bool AddressSaType(vector<int>&data1,vector<int>&data2,vector<int>&data){//�ж�������ַ�Ƿ�����ͬһ����ַ�Լ���ַ��Χ�Ƿ���ȷ 
	if((data1[0]>=1&&data1[0]<=127&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=1&&data2[0]<=126&&data2[3]>=0&&data2[3]<=255)){//�ж�������ַ�Ƿ�ΪA���ַ 
		data[0]=1;
		return true;  
	} 
	else if((data1[0]>=128&&data1[0]<=191&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=128&&data2[0]<=191&&data2[3]>=0&&data2[3]<=255)){//�ж�������ַ�Ƿ�ΪB���ַ 
		data[1]=1;
		return true;
	}
	else if((data1[0]>=192&&data1[0]<=223&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=192&&data2[0]<=223&&data2[3]>=0&&data2[3]<=255)){//�ж�������ַ�Ƿ�ΪC���ַ 
		data[2]=1;
		return true;
	}
	else if((data1[0]>=224&&data1[0]<=239&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=224&&data2[0]<=239&&data2[3]>=0&&data2[3]<=255)){//�ж�������ַ�Ƿ�ΪD���ַ 
		data[3]=1;
		return true;
	}
	else if((data1[0]>=240&&data1[0]<=255&&data1[3]>=0&&data1[3]<=255)&&(data2[0]>=240&&data2[0]<=255&&data2[3]>=0&&data2[3]<=255)){//�ж�������ַ�Ƿ�ΪE���ַ 
		data[4]=1;
		return true;
	}
	return false;
}

bool SameNet(vector<int>&M_data,vector<int>&A_data,vector<int>&B_data,int cnt){//�ж�����IP��ַ�Ƿ�����ͬһ�������� 
	if(CheckMaValid(M_data,cnt)&&CheckIPValid(A_data)&&CheckIPValid(B_data)){ 
		for(int i=0;i<M_data.size();i++){
			if((M_data[i]&A_data[i])!=(M_data[i]&B_data[i])) {
				return false;
			}
		}
		return true;
	}else return false;
} 

void AddressType(vector<int>&data){//�ж�IP��ַ������ 
	char ag[5]={'A','B','C','D','E'};
	for(int i=0;i<5;i++){
		if(data[i]) cout<<"��ַ����Ϊ" <<ag[i]<<"���ַ"<<endl;
	}
}

int SubnetNumber(int number){//�������ֵĸ����ж� 
	int redouble[8]={1,2,4,8,16,32,64,128};
	for(int i=0;i<8;i++){
		if(number==1)return 0;
		if(number>redouble[i]&&number<=redouble[i+1]){
			return i+1;
		}
	}
	return -1;
}

void SubnetPrintf(vector<int>&data,int cnt,char type){//��ӡ�������ֺ�ĵ�ַ 
	int number[9]={0,128,64,32,16,8,4,2,1}; 
	int redouble[8]={1,2,4,8,16,32,64,128};
	switch(type){
		case 'A': 
			cout<<"A��ַ���������ַ�ΧΪ��"<<endl;
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
			cout<<"B��ַ���������ַ�ΧΪ��"<<endl;
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
			cout<<"C��ַ���������ַ�ΧΪ��"<<endl;
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
