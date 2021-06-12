#include<iostream>
#include<math.h>
#include<string>
#include<fstream>
#include<Windows.h>
using namespace std;

class Post;
class User;
class Page;
class Object;

class Helper
{
public:
	static bool compare(char* str, char*str1) {

		int lenstr = Helper::StringLenght(str);
		int lenstr1 = Helper::StringLenght(str1);
		if (lenstr == lenstr1)
		{
			for (int i = 0; str[i] != '\0'; i++)
			{
				if (str[i] != str1[i])
					return false;

			}
			return true;

		}
		else {
			return false;
		}

	}
	static int StringLenght(char* str)
	{
		int stringLen = 0;
		for (char* temp = str; *temp != '\0'; temp++)
			stringLen++;
		return stringLen;
	}
	static char* GetStringFromBuffer(char* str)
	{
		int strLen = StringLenght(str);
		char* buffer = 0;

		if (strLen > 0)
		{
			buffer = new char[strLen + 1];
			char* tempDest = buffer;

			for (char* tempSrc = str; *tempSrc != '\0'; tempSrc++, tempDest++)
			{
				*tempDest = *tempSrc;
			}
			*tempDest = '\0';
		}
		return buffer;
	}
};
class Date
{
	int Day;
	int Month;
	int Year;
public:
	static Date CurrentDate;
	Date(int a=0,int b=0,int c=0 )
	{
		Day = a;
		Month = b;
		Year = c;
	}
	static void setcurrentdate(int d,int m,int y){
		CurrentDate.Day = d;
		CurrentDate.Month = m;
		CurrentDate.Year = y;

	}
	~Date()
	{
		// no need of destructor
	}
	static void PrintDate() {

		cout << "System Date :" << CurrentDate.Day << "/" << CurrentDate.Month << "/" << CurrentDate.Year << endl;
	}
	void Print() {

		cout << "System Date :" << Day << "/" <<Month << "/" << Year << endl;
	}

	void setDates(int A,int B,int C){
		Day = A;
		Month = B;
		Year = C;
	}
	static int getcurrentday(){
		
		return CurrentDate.Day;
	}
	 int getDay() {
		return Day;
	}
	int getMonth() {
		return Month;
	}
	int getYear() {
		return Year;
	}


};
Date Date::CurrentDate(18,12,1999);
class Object
{
private:
	char* ID;
public:

	Object()
	{
		ID = nullptr;
	}

	char* GetID() {
		return ID;
	}
	virtual void PrintListView() = 0;
	void SetID(char* A) {
		ID = Helper::GetStringFromBuffer(A);
	}
	~Object() {
		//destructor
		if (ID != nullptr)
			delete ID;
	}


};
class Comment :public Object
{
private:

	char* ComDescription;
	Object* Commentby;
public:
	Comment() {
		ComDescription = nullptr;
		Commentby = nullptr;
	}
	void SetCommentby(Object* A) {
		Commentby = A;
	}

	void setCID(char* ptr) {

		SetID(ptr);
	}
	void Setdescp(char* ptr) {
		ComDescription = ptr;

	}
	char* GetCID() {

		return GetID();
	}
	char* Getdescp() {
		return ComDescription;
	}
	void PrintListView() {

		if (Commentby != nullptr)
			Commentby->PrintListView();

		cout << "--" << ComDescription << endl;
	}
	~Comment() {
		//destructor
		if (ComDescription != nullptr)
			delete[] ComDescription;
	}

};
class Post :public Object
{
private:
	char* description;
	int noOflikes;
	char* shared;
	char* userpagesliked[10];
	Object* SharedBy;
	Object**LikedBy;
	Date Dofpost;
	int totalComments;
	Comment** comments;
	//Comments Cofpost;
public:
	char* GetIDP() {
		char*ptr = GetID();
		return ptr;
	}
	void SetDopost(Date A){
		
		Dofpost.setDates(A.getDay(),A.getMonth(),A.getYear());

	}
	int DayOfDofpost(){
		
		return Dofpost.getDay();
	}
	void setTotalComments(int index)
	{
		totalComments = index;
	}
	void SetSharedby(Object* A);
	void setDesc(char* des)
	{
		description = Helper::GetStringFromBuffer(des);
	}
	char* Getdes() {
		return description;
	}
	void SetLikedby(Object* A);
	void AddComment(int index, Comment*A)
	{
		comments[index] = A;
	}
	void AddnewComment(int index, Comment*A, Object* B)
	{
		comments[index] = new Comment;
		comments[index]->setCID(Helper::GetStringFromBuffer(A->GetCID()));
		comments[index]->Setdescp(Helper::GetStringFromBuffer(A->Getdescp()));
		comments[index]->SetCommentby(B);
	}

	Post() {
		description = nullptr;
		noOflikes = 0;
		SharedBy = nullptr;
		LikedBy = nullptr;
		comments = nullptr;
		for (int i = 0; i < 10; i++)
			userpagesliked[i] = nullptr;
		shared = nullptr;

	}


	~Post() {
		if (description != nullptr)
			delete[]description;
		if (shared != nullptr)
			delete shared;
		for (int i = 0; i < totalComments; i++)
			delete comments[i];
		if (comments != nullptr)
			delete[] comments;

		delete[] LikedBy;
		//destructor
	}
	void Printapost() {
		cout << description << endl;
		Dofpost.Print();
	}
	void PrintLikedBy()
	{
		if (LikedBy != 0)
		{
			for (int i = 0; i< noOflikes; i++)
			{
				//This is polymorphism
				LikedBy[i]->PrintListView();
				cout << endl;
			}
		}

	}
	void PrintComments() {

		for (int i = 0; i < totalComments; i++)
		{
			if (comments[i] != nullptr)
				comments[i]->PrintListView();
		}

	}
	bool checkREP(Object * A)
	{
		for (int i = 0; i < noOflikes; i++)
		{
			if (Helper::compare(LikedBy[i]->GetID(), A->GetID()))
			{
				return true;
				break;
			}
		}
		return false;
	}
	void PrintListView()
	{
		SharedBy->PrintListView();
		cout << "    shared--";
		cout << description<<" "; 
		Dofpost.Print();
			cout<< endl;
	}
	void allocateTotalComments()
	{
		comments = new Comment*[10];
	}
	void PrintPost()
	{
		PrintListView();
		cout << endl;
		PrintComments();
	}
	void Loadposts(ifstream& inp)
	{
		char buffer[80];
		inp >> buffer;
		SetID(buffer);
		//cout << GetID() << endl;

		inp.getline(buffer, 80);
		int temp,a,s;
		inp >> temp;
		inp >> a;
		inp >> s;
		Dofpost.setDates(temp,a,s);
		inp.getline(buffer, 80);
		inp.getline(buffer, 80);
		description = Helper::GetStringFromBuffer(buffer);
		//cout << description << endl;
		inp >> buffer;
		shared = Helper::GetStringFromBuffer(buffer);
		//cout << shared<<endl;
		inp.getline(buffer, 80);
		int i = 0;
		while (buffer[0] != 45)
		{
			inp >> buffer;
			if (buffer[0] != 45)
			{
				userpagesliked[i] = Helper::GetStringFromBuffer(buffer);
				//cout << userpagesliked[i];
				noOflikes++;
			}

			i++;
		}
		inp.getline(buffer, 80);
		AllocateLB();
	}
	void NameofPerson(int a) {
		SharedBy[a].PrintListView();
	}
	void SettingNewLiker(int ind, Object*A) {
		LikedBy[ind] = A;
	}
	void AllocateLB() {
		LikedBy = new Object*[10];
	}
	int gettotalcomments() {
		return totalComments;
	}
	int count = 0;
	int GetNoflikes();


	char** Getuserpagesliked() {
		return userpagesliked;
	}
	char* Getshared() {
		return shared;
	}
	void Setlikes(int a) {
		noOflikes = a;
	}

};
void Post::SetSharedby(Object* A)
{
	SharedBy = A;
}
void Post::SetLikedby(Object* A) {
	LikedBy[count++] = A;
}
int Post::GetNoflikes() {
	return noOflikes;
}
class Page :public Object
{
private:
	char* title;
	Post** timeline;
	int noOfPosts;
	int postsCount;
	int likeCount;
	User* likedUsers;
public:
	Page() {
		title = nullptr;
		timeline = nullptr;
		likedUsers = nullptr;
		likeCount = 0;
		noOfPosts = 10;
		postsCount = 0;
	}
	void Loadpages(ifstream& inp) {
		char buffer[80];
		inp >> buffer;
		//cout << buffer;
		SetID(buffer);
		// << ID;
		inp.getline(buffer, 80);
		for (int i = 0; buffer[i] != '\0'; i++)
		{
			buffer[i] = buffer[i + 1];
		}

		title = Helper::GetStringFromBuffer(buffer);
		//cout << title << endl;
		Allocation();
	}
	int getNoOfpost() {

		return noOfPosts;
	}
	void Viewapost()
	{
		int Cday = Date::getcurrentday();

		for (int i = 0; i < postsCount; i++)
		{
			int day = timeline[i]->DayOfDofpost();
			if (Cday==day || (Cday-1)==day)
			{
				timeline[i]->PrintPost();
				cout << endl;
			}
		}
	}
	void SetnoOfpost(int a)
	{
		noOfPosts = a;
	}
	void Allocation()
	{
		timeline = new Post*[noOfPosts];
	}
	void AddPostInTimeline(Post* ptr)
	{
		timeline[postsCount] = ptr;
		postsCount++;
	}
	void printapost(int a) {
		timeline[a]->PrintListView();
	}
	char* gettitle() {

		return title;
	}
	void PrintListView()
	{
		cout << GetID() << "-" << title;
	}
	~Page() {
		delete title;

		for (int i = 0; i < postsCount; i++)
			delete timeline[i];

		if (timeline != nullptr)
			delete[]timeline;

		//destructor
	}
};
class User :public Object
{
private:
	char* firstname;
	char* lastname;
	User** friends;
	char* friendlist[10];
	int noFriends;
	int noPages;
	int noOfPost;
	Page** likedpages;
	char* pagelist[10];
	Post** posts;
	Post** Likedpost;
public:
	void Allocatefriends(int);
	void Allocatepages(int);
	User() {
		firstname = nullptr;
		lastname = nullptr;
		noFriends = 0;
		noPages = 0;
		for (int i = 0; i < 10; i++)
			friendlist[i] = nullptr;
		for (int i = 0; i < 10; i++)
			pagelist[i] = nullptr;
		posts = nullptr;
		noOfPost = 0;
	}
	int friendcount = 0;
	int pagescount = 0;
	void printaPost(int ind) {
		posts[ind]->Printapost();
	}
	void Printapostonpage(){
		for (int i = 0; i < noOfPost; i++)
		{
			int Cday = Date::getcurrentday();
			int day = posts[i]->DayOfDofpost();
			if (Cday==day || (Cday-1)==day)
			{
				posts[i]->PrintListView();
				posts[i]->PrintComments();

			}

		}
	}
	void LoadUsers(ifstream& inp) {

		char buffer[80];
		inp >> buffer;
		SetID(buffer);
		inp >> buffer;
		//cout << buffer << " ";
		firstname = Helper::GetStringFromBuffer(buffer);
		inp >> buffer;
		//cout << buffer << " ";
		lastname = Helper::GetStringFromBuffer(buffer);
		int i = 0;
		while (buffer[0] != '-')
		{
			inp >> buffer;
			if (buffer[0] != '-') {
				friendlist[i] = Helper::GetStringFromBuffer(buffer);
				//cout << friendlist[i] << endl;
				friendcount++;

			}
			//cout << buffer << " ";
			i++;
		}
		inp >> buffer;
		//cout << endl;
		i = 0;
		while (buffer[0] != 45)
		{
			if (buffer[0] != 45)
			{
				pagelist[i] = Helper::GetStringFromBuffer(buffer);
				//cout << pagelist[i] << endl;
				pagescount++;
			}
			inp >> buffer;
			i++;
		}
		Allocatefriends(friendcount);
		Allocatepages(pagescount);
		AllocationOfPost();
		inp.getline(buffer, 80);
	}
	void PrintFriendsofUser() {
		for (int i = 0; i < friendcount; i++)
		{
			
			friends[i]->Printapostonpage();
			cout << endl;
		}

	}
	void PrintPagesofUser() {
		for (int i = 0; i <noPages; i++)
		{
			likedpages[i]->Viewapost();
			cout << endl << endl;

		}
	}

	void viewhome() {
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "-------------------------------------HOME--------------------------------------" << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		PrintFriendsofUser();
		cout << endl;
		PrintPagesofUser();

	}
	void viewtimeline() {
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "-------------------------------------TimeLine----------------------------------" << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < noOfPost; i++)
		{
			posts[i]->PrintListView();
			posts[i]->PrintComments();
			cout << endl << endl;

		}
	}
	char** getfriendlist() {
		return friendlist;
	}
	char** getpagelist() {
		return pagelist;
	}

	char* getID() {
		return GetID();
	}
	char* getfname()
	{
		return firstname;
	}
	char* getlname() {

		return lastname;
	}
	void viewFriendlist() {

		cout << firstname << " " << lastname << "- Friend List" << endl;

		for (int i = 0; i < friendcount; i++)
		{
			//cout << "test";
			friends[i]->PrintListView();
			cout << endl;
		}
	}
	void PrintListView() {
		cout << getID() << "-" << firstname << " " << lastname;
	}

	void viewLikedPages() {

		cout << firstname << " " << lastname << "- Liked pages" << endl;

		for (int i = 0; i < pagescount; i++)
		{
			//cout << "test";
			likedpages[i]->PrintListView();
			cout << endl;
		}
	}
	void AllocationOfPost() {
		posts = new Post*[10];
	}
	void AddPost(Post* A)
	{
		posts[noOfPost++] = A;
	}
	void Addfriend(User*A) {
		friends[noFriends++] = A;

	}

	void Addpages(Page*A) {
		likedpages[noPages++] = A;

	}
	void SharenewPost(char*buffer, char*des, Object*A) {
		int index = noOfPost;
		posts[index] = new Post;
		posts[index]->SetID(buffer);
		posts[index]->setDesc(des);
		posts[index]->SetSharedby(A);
		posts[index]->SetDopost(Date::CurrentDate);
		noOfPost++;
	}
	~User() {
		if (firstname != nullptr)
			delete firstname;
		if (lastname != nullptr)
			delete lastname;
		for (int i = 0; i < 10; i++)
		{
			if (friendlist[i] != nullptr)
				delete friendlist[i];
		}
		for (int i = 0; i < 10; i++)
		{
			if (pagelist[i] != nullptr)
				delete pagelist[i];
		}
		if (friends != nullptr)
			delete[]friends;
		if (likedpages != nullptr)
			delete[]likedpages;
		for (int i = 0; i < noOfPost; i++)
			delete posts[i];
		delete[] posts;
		//destructor
	}
};
void User::Allocatefriends(int a) {
	friends = new User*[a];
}
void User::Allocatepages(int a) {
	likedpages = new Page*[a];
}
class Facebook
{
private:
	User ** Users;
	Page** Pages;
	Post** Posts;
	User* Currentuser;
	Date Currentdate;
public:
	void Run();
	int totalusers;
	int totalpages;
	int totalposts = 0;
	int totalcomments = 0;
	Facebook() {
		Users = nullptr;
		Pages = nullptr;
		Posts = nullptr;
		Currentuser = nullptr;

	}
	
	void LoadData() {
		ifstream inp;
		inp.open("Users.txt");
		inp >> totalusers;
		char buffer[80];
		inp.getline(buffer, 80);
		Users = new User*[totalusers];

		for (int i = 0; i < totalusers; i++)
		{
			Users[i] = new User;
			Users[i]->LoadUsers(inp);
		}
		ifstream inpp;
		inpp.open("Pages.txt");
		inpp >> totalpages;
		inpp.getline(buffer, 80);
		Pages = new Page*[totalpages];

		for (int i = 0; i < totalpages; i++)
		{
			Pages[i] = new Page;
			Pages[i]->Loadpages(inpp);
		}
		inp.close();
		inpp.close();
		ifstream inppo;
		inppo.open("Posts.txt");
		inppo >> totalposts;
		inppo.getline(buffer, 80);
		Posts = new Post*[totalposts];

		inppo.getline(buffer, 80);
		inppo.getline(buffer, 80);
		inppo.getline(buffer, 80);
		inppo.getline(buffer, 80);
		inppo.getline(buffer, 80);
		inppo.getline(buffer, 80);

		for (int i = 0; i < totalposts; i++)
		{
			inppo.getline(buffer, 80);
			//cout << buffer << endl;
			Posts[i] = new Post;
			Posts[i]->Loadposts(inppo);
		}

		ifstream inpc;
		inpc.open("Comments.txt");
		inpc >> totalcomments;
		//cout << totalcomments;
		char buffer1[500];
		int *index1 = new int[totalcomments];
		for (int i = 0; i < totalcomments; i++)
			index1[i] = 0;
		inpc.getline(buffer1, 500);
		inpc.getline(buffer1, 500);
		inpc.getline(buffer1, 500);

		for (int i = 0; i < totalposts; i++)
			Posts[i]->allocateTotalComments();

		while (!inpc.eof())
		{

			Comment* Comments = new Comment;
			inpc >> buffer1;
			//cout << buffer1;
			Comments->setCID(buffer1);

			//cout << Comments[i]->GetCID();

			inpc >> buffer1;
			//cout << buffer1;
			int Postind = getPostid(buffer1);
			//cout<<Comments[i]->GetPocom();
			inpc >> buffer1;
			//cout << buffer1;

			//cout<<Comments[i]->GetPoster();
			int index = getidfromID(buffer1);

			if (buffer1[0] == 'u')
			{
				Comments->SetCommentby(Users[index]);
				//				Comments->PrintListView();
			}
			else {
				Comments->SetCommentby(Pages[index]);
			}
			inpc.getline(buffer1, 500);
			//cout << buffer1;
			Comments->Setdescp(Helper::GetStringFromBuffer(buffer1));
			//cout<<Comments[i]->Getdescp() << endl;

			Posts[Postind]->AddComment(index1[Postind], Comments);
			index1[Postind]++;
			Posts[Postind]->setTotalComments(index1[Postind]);
		}

		Linking();
	}
	void Linking() {
		char** friendsid;
		char** pageids;
		for (int i = 0; i < totalusers; i++)
		{
			friendsid = Users[i]->getfriendlist();
			pageids = Users[i]->getpagelist();
			for (int j = 0; friendsid[j] != 0; j++)
			{
				int index = getidfromID(friendsid[j]);
				//cout << index << endl;
				Users[i]->Addfriend(Users[index]);
			}
			for (int j = 0; pageids[j] != 0; j++)
			{
				//cout << friendsid[j] << endl;
				int index = getidfromID(pageids[j]);
				//cout << index << endl;
				Users[i]->Addpages(Pages[index]);
			}
			//cout << endl;
		}

		//cout << Posts[5]->Getshared();
		for (int i = 0; i < totalposts; i++)
		{
			char*ptr = Posts[i]->Getshared();
			int len = getidfromID(ptr);

			if (ptr[0] == 'u')
			{
				Posts[i]->SetSharedby(Users[len]);
				Users[len]->AddPost(Posts[i]);
			}
			else if (ptr[0] == 'p')
			{
				Posts[i]->SetSharedby(Pages[len]);
				Pages[len]->AddPostInTimeline(Posts[i]);
			}
			char** ptr1 = Posts[i]->Getuserpagesliked();
			for (int j = 0; j < Posts[i]->GetNoflikes(); j++)
			{
				int ind = getidfromID(ptr1[j]);
				if (ptr1[j][0] == 'u')
					Posts[i]->SetLikedby(Users[ind]);
				else
					Posts[i]->SetLikedby(Pages[ind]);
			}

		}
	}
	int getidfromID(char* str) {

		int len = Helper::StringLenght(str);
		if (len == 2) {
			int ind = str[1] - 48;
			return (ind - 1);
		}
		else
		{
			int ind = 0;
			int power;
			int num;
			int i = 1;
			while (i <= len)
			{
				power = pow(10, len - 2);
				num = str[i] - 48;
				ind += (num*power);
				len--;
				i++;
			}
			return (ind - 1);
		}

	}

	int getPostid(char* str) {

		int len = Helper::StringLenght(str);
		int ind = 0;
		int power;
		int num;
		int i = 4;
		while (i <= len)
		{
			power = pow(10, len - 5);
			num = str[i] - 48;
			ind += (num*power);
			len--;
			i++;
		}
		return (ind - 1);


	}
	void Addlike(char *ID)
	{

		for (int i = 0; i < totalposts; i++)
		{
			if (Helper::compare(ID, Posts[i]->GetID()))
			{
				if (!(Posts[i]->checkREP(Currentuser)) && Posts[i]->GetNoflikes() < 10)
				{
					int likes = Posts[i]->GetNoflikes();
					Posts[i]->SettingNewLiker(likes, Currentuser);
					Posts[i]->Setlikes(likes + 1);
				}
			}
		}
	}
	void Sharepost(char* buffer) {
		char*  description;
		for (int i = 0; i < totalposts; i++)
		{
			if (Helper::compare(buffer, Posts[i]->GetID()))
			{
				description = Posts[i]->Getdes();
			}
		}
		char buffer1[8];
		int total = totalposts + 1;
		if (totalposts>9)
		{
			buffer1[0] = 'p';
			buffer1[1] = 'o';
			buffer1[2] = 's';
			buffer1[3] = 't';

			int j = 1;
			int sum = total;

			int i = 0;
			sum = total;
			while (sum != 0) {
				sum = sum / 10;
				i++;
			}
			buffer1[i + 4] = 0;
			i--;
			i = i + 4;
			sum = total;
			while (sum != 0) {
				int num = sum % 10;
				sum = sum / 10;
				buffer1[i] = num + 48;
				i--;
			}



		}
		else
		{
			buffer1[0] = 'p';
			buffer1[1] = 'o';
			buffer1[2] = 's';
			buffer1[3] = 't';
			buffer1[4] = total + 48;
			buffer1[5] = '/0';
		}
		Currentuser->SharenewPost(buffer1, description, Currentuser);

	}
	void AddComment(char*buffer, char*buffer1) {
		int index = getPostid(buffer);
		char newbuffer[6];
		int total = totalcomments + 1;
		if (totalcomments>9)
		{
			newbuffer[0] = 'c';
			int j = 1;
			int sum = total;

			int i = 0;
			sum = total;
			while (sum != 0) {
				sum = sum / 10;
				i++;
			}
			newbuffer[i] = 0;
			i--;
			sum = total;
			while (sum != 0) {
				int num = sum % 10;
				sum = sum / 10;
				newbuffer[i] = num + 48;
				i--;
			}



		}
		else
		{
			newbuffer[0] = 'c';
			newbuffer[1] = total + 48;
			newbuffer[2] = '/0';

		}
		for (int i = 0; i < totalposts; i++)
		{
			if (Helper::compare(buffer, Posts[i]->GetID()))
			{
				int numOFcom = Posts[i]->gettotalcomments();
				if (numOFcom < 10)								//comments check;
				{
					Comment *temp = new Comment;
					temp->Setdescp(buffer1);
					temp->setCID(newbuffer);
					//Posts[i]->allocateCommentWithIndex(n);
					Posts[i]->AddnewComment(numOFcom, temp, Currentuser);
					Posts[i]->setTotalComments(numOFcom + 1);
					break;
				}
				else
					cout << "Already 10 comments on the post";
			}
		}

	}
	void SpecificPost(char* buffer)
	{
		bool found = false;
		for (int i = 0; i <totalposts; i++)
		{
			if (Helper::compare(buffer, Posts[i]->GetIDP()))			//searching post
			{
				if (Posts[i]->GetNoflikes() > 0)									//likes check
				{
					cout << "Likers of " << buffer << " are:\n";
					cout << endl;
					Posts[i]->PrintLikedBy();
					found = true;
					break;
				}
			}
		}
		if (!found)
			cout << "No Likes on the Post.\n";
	}
	void ViewPost(char* buffer) {

		for (int i = 0; i < totalposts; i++)
		{
			if (Helper::compare(buffer, Posts[i]->GetID()))
			{
				Posts[i]->PrintPost();

			}
		}

	}
	void Viewapost(char* buffer)
	{
		int id = getidfromID(buffer);
		{
			Pages[id]->Viewapost();
		}
	}
	void SetCurrentUser(char* ID)
	{
		int i = 0;
		while (i<totalusers)
		{
			char* newid = Users[i]->getID();
			if (Helper::compare(ID, newid))
			{
				Currentuser = Users[i];
				break;
			}
			i++;
		}
		cout << Users[i]->getfname() << " " << Users[i]->getlname() << " succesfully set as current user" << endl;

	}
	bool matchString(char *str, char *toFind) {
		for (int i = 0; str[i]; i++) {
			if (str[i] == toFind[0]) {
				int j = 0;
				while (str[i++] == toFind[j++]);
				if (j == Helper::StringLenght(toFind) + 1)
					return true;
			}
		}
		return false;
	}
	void Searchfunction(char* buffer)
	{
		cout << "Users" << endl;
		for (int i = 0; i < totalusers; i++)
		{
			if (Helper::compare(buffer, Users[i]->getfname()) || Helper::compare(buffer, Users[i]->getlname()))
			{
				Users[i]->PrintListView();
				cout << endl;
			}
		}
		cout << "Posts" << endl;
		for (int i = 0; i < totalposts; i++) {
			if (matchString(Posts[i]->Getdes(), buffer)) {
				Posts[i]->PrintListView();
				cout << endl;
			}
		}
		cout << "Pages" << endl;
		for (int i = 0; i < totalpages; i++) {
			if (matchString(Pages[i]->gettitle(), buffer)) {
				Pages[i]->PrintListView();
				cout << endl;
			}
		}
	}
	~Facebook() {
		for (int i = 0; i < totalusers; i++)
		{
			if (Users[i] != nullptr)
				delete Users[i];

		}
		delete[]Users;
		for (int i = 0; i < totalpages; i++)
		{
			if (Pages[i] != nullptr)
				delete Pages[i];

		}
		delete[]Pages;
		delete[]Posts;
	}

};
void Facebook::Run()
{


	cout << "Today's Date:\t";
	Date::setcurrentdate(15, 11, 2017);
	Currentdate.PrintDate();

	SetCurrentUser("u7");
	cout << endl;

	cout << endl;

	//	cout << "Current User:\t" << Currentuser->GetID() << endl;
	//cout << "User Name:\t" << Currentuser->getfname() <<" "<<Currentuser->getlname()<< endl;
	cout << endl;
	Currentuser->viewFriendlist();
	cout << endl;
	Currentuser->viewLikedPages();

	cout << "\nCommand:\t Home Of User\n";
	cout << endl;
	Currentuser->viewhome();

	cout << "Command:\t Timeline OF User \n";
	Currentuser->viewtimeline();

	cout << "-------------------------------------------------------------------------------" << endl;

	cout << "Command: \t ViewlikedPost(post5) \n";
	cout << "Post Liked by: \n";
	SpecificPost("post5");
	cout << "-------------------------------------------------------------------------------" << endl;

	cout << "Command:\t likePost(post5) \n";
	Addlike("post5");
	cout << "Command:\t ViewlikedPost(post5) \n";
	cout << "Post Liked by:\n";
	SpecificPost("post5");
	cout << "-------------------------------------------------------------------------------" << endl;


	cout << "Command:\t  PostComment(post4,Goodluck for your result)  \n";
	char buffer[80] = "Goodluck for your result.";
	AddComment("post4", buffer);

	cout << "Command: \t ViewPost(post4) \n";
	ViewPost("post4");

	cout << "-------------------------------------------------------------------------------" << endl;

	cout << "Command::\tPostComment(post8,Thanks for the wishes)\n";
	char buffer1[80] = "Thanks for the wishes.";
	AddComment("post8", buffer1);
	cout << "Command: \t ViewPost(post8) \n";
	ViewPost("post8");
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Command: \t Sharepost (post5) \n";
	Sharepost("post5");
	cout << "Command: \t Timeline Of User \n";
	Currentuser->viewtimeline();

	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Command:\t  Viewapost(p1) \n";
	Viewapost("p1");
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Command:\t  Searching(""Birthday"") \n";
	Searchfunction("Birthday");
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Command:\t  Searching(""Ali"") \n";
	Searchfunction("Ali");
}
int main()
{
	
	/*char FB1[50];
	cout << "Enter ID--";
	cin >> FB1;
	cout << endl;
	cout << "Enter Password--";
	cin >> FB1;
	cout << endl;
	system("color 1");
	{cout << "-------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------FACEBOOK----------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	Sleep(1000);
	}
	cout << endl;
	cout << endl;
	system("cls");
	system("color 4");
	cout << "###############################################################################" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------LOADING-----------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "###############################################################################" << endl;

	for (int i = 0; i < 25; i++)
	{
	cout << "[-]";
	Sleep(150);

	}
	cout << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << endl;
	system("cls");
	system("color F");
	*/
	Facebook FB;
	FB.LoadData();
	FB.Run();
	system("pause");
	return 0;
}