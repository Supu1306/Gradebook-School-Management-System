//Name- Supreet Singh Dhillon
//id- DHISD1903
#include <iostream>
#include <string>
#include <ctime>
#include <cassert>
using namespace std;

template <class T>
class SmarterArray
{
private:
	T *A;
	int size;

public:
	//Constructors
	SmarterArray(); //Implemented for you
	SmarterArray(const T*, const int&); //Non-default constructor: Deep copy of the argument
	SmarterArray(const SmarterArray<T>&); //Copy constructor: Deep copy of the argument

	//Assignment operator
	SmarterArray<T>& operator = (const SmarterArray<T>&); //Assignment operator. Memory clean up and deep copy of the argument

	//Destructor
	~SmarterArray(); //Destructor. Memory clean up

	//Getters, Setters, operators and other functions
	int getSize() const; //Return the size of the calling object
	T& operator[](const int&) const; //Assert index is valid and then return the element at the given index
	int find(const T&) const; //Return the index of the element that is == to the argument. Return -1 if not found.
	void append(const T&); //Append the argument to the calling object.
	bool remove(const int&); //If the index argument is a valid index, then remove the element at the index argument
							//from the calling object and return true. Otherwise return false. 
							//You don't need to assert the index argument.
	bool operator == (const SmarterArray<T>&) const; //return true if sizes are equal and elements at same indexes are ==
	
	template <class T>
	friend ostream& operator << (ostream&, const SmarterArray<T>&); //Implemented for you
};

template <class T>
SmarterArray<T>::SmarterArray()
{
	this->A = nullptr;
	this->size = 0;
}
template <class T>
ostream& operator << (ostream& out, const SmarterArray<T>& L)
{
	if (L.getSize() == 0)
		out << "[Empty List]";
	else
	{
		for (int i = 0; i < L.getSize()-1; i++)
			out << L[i] << endl;
		out << L[L.getSize()-1] << endl;
	}
	return out;
}
template <class T>
SmarterArray<T>::SmarterArray(const T*A,const int &s)
{
	this->size=s;
	if(this->getSize()>0)
	{
		this->A =new T[this->getSize()];
		for(int i=0;i <this->getSize();i++)
			this->A[i]= A[i];
	}
}
template<class T>
SmarterArray<T>::SmarterArray(const SmarterArray<T> &a)
{
	this->size=a.getSize();
	if(this->getSize()>0)
	{
		this->A = new T[this->getSize()];
		for(int i=0;i<this->getSize();i++)
			this->A[i]=a[i];
	}
}

template<class T>
SmarterArray<T>& SmarterArray<T> :: operator = (const SmarterArray<T> &a)
{
	if(this== &a)
		return *this;

	this->~SmarterArray();
	this->size=a.getSize();

	if(this->getSize()>0)
	{
		this->A=new T[this->getSize()];
		for(int i=0;i<this->getSize();i++)
			this->A[i]=a[i];
	}
	return *this;
}
template<class T>
SmarterArray<T>::~SmarterArray()
{
	if(this->getSize()>0)
	{
		delete[]this->A;
		this->size=0;
		A=nullptr;
	}
}

template<class T>
int SmarterArray<T>::getSize()const
{
	return this->size;
}

template<class T>
T& SmarterArray<T>::operator[](const int& i)const
{
	if(i<0 && i >=this->getSize())
	{
		cout<< " ERROR! Index out of bounds."<<endl;
	}
	return this->A[i];
}

template <class T>
int SmarterArray<T>::find(const T& a) const
{
	for(int i=0;i<this->getSize();i++)
		if(this->A[i]==a)
			return i;
	return -1;
}

template <class T>
void SmarterArray<T>::append(const T &a)
{
	T *x= new T[this->getSize() +1];

	for(int i=0;i<this->getSize();i++)
		x[i]=this->A[i];

	x[this->getSize()]=a;

	if(this->getSize() > 0)
		delete[] this->A;

	this->A=x;
	this->size+=1;
}

template<class T>
bool SmarterArray<T>::remove(const int & index)
{

	if(index<0 || index>=this->getSize())
		return false;
	else
	{

		T *y = new T[this->getSize()-1];

		for(int i=0;i<index;i++)
			y[i]=this->A[i];
		for(int i=index+1; i<this->getSize();i++)
			y[i-1]=this->A[i];

		if(this->getSize()>0)
			delete[]this->A;

		this->A=y;
		this->size -=1;
		return true;
	}
}

template<class T>
bool SmarterArray<T>::operator == (const SmarterArray<T>& a) const 
{
	bool answer=0;
	if(this->size!=a.size)
		return answer;
	else
	{
		for(int i=0;i<this->size;i++)
		{
			if((*this)[i]!=a[i])
				return answer;
		}
		return 1;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class V>
class Map
{
private:
	K *A1; //The keys of the map
	V *A2; //The values of the map
	int size; //The size of the map (Both A1 and A2 have the same size at any time by design)

public:
	//Constructors
	Map(); //Implemented for you
	Map(const Map<K, V>&); //Copy constructor. Deep copy.

	//Assignment operator
	Map<K, V>& operator = (const Map<K, V>&); //Assignment operator. Memory clean up and deep copy.

	//Destructor
	~Map(); //Destructor.

	//Getters, Setters, operators and other functions
	int getSize() const; //Return the common size of the map.
	int find(const K&) const; //Return the index of the first element of the Keys array == the argument. Return -1 if not found.
	int find(const V&) const; //Return the index of the first element of the Values array == the argument. Return -1 if not found.
	K& operator[](const V&) const; //Assert the argument is found in the Values array and then return the key with the given value 
	V& operator[](const K&) const; //Assert the argument is found in the Keys array and then return the value with the given key
	K& keyAtIndex(const int&) const; //Assert the index argument and then return the key at the given index
	V& valueAtIndex(const int&) const; //Assert the index argument and then return the value at the given index
	void append(const K&, const V&); //Append the key-value pair to the calling object
	bool remove(const int&); //If the index argument is a valid index, then remove the key-value pair at the index argument
							//from the calling object and return true. Otherwise return false. 
							//You don't need to assert the index argument.

	template <class K, class V>
	friend ostream& operator << (ostream&, const Map<K, V>&); //Implemented for you
};

template <class K, class V>
Map<K, V>::Map()
{
	A1 = nullptr;
	A2 = nullptr;
	size = 0;
}
template <class K, class V>
ostream& operator << (ostream& out, const Map<K, V>& m)
{
	if (m.size == 0)
		out << "[Empty Map]" << endl;
	else
	{
		for (int i = 0; i < m.size; i++)
			out << m.A1[i] << ", " << m.A2[i] << endl;
	}
	return out;
}

template<class K, class V>
Map<K,V>::Map(const Map<K,V>& a)
{
	size = a.size;
	if (size > 0)
	{
		A1 = new K[size];
		A2 = new V[size];
		for (int i = 0; i < size; i++)
		{
			A1[i] = a.A1[i];
			A2[i] = a.A2[i];
		}
	}
}

template<class K, class V>
Map<K, V>& Map<K, V>::operator= (const Map<K, V>& a)
{
	if (this == &a)
		return *this;
	else
	{
		(*this).~Map();
		size = a.size;
		if (size > 0)
		{
			A1 = new K[size];
			A2= new	 V[size];
			for (int i = 0; i < size; i++)
			{
				A1[i] = a.A1[i];
				A2[i] = a.A2[i];
			}
		}
		return *this;
	}
}
template<class K, class V>
Map<K, V>::~Map()
{
	if (size > 0)
	{
		delete[] A1;
		delete[] A2;
		size = 0;
	}
}
template<class K, class V>
int Map<K,V>::getSize() const
{
	return size;
}
template <class K, class V>
int Map<K,V>::find(const K& v)const
{
	for(int i=0;i<this->getSize();i++)
		if(this->A1[i]==v)
			return i;
	return -1;
}

template <class K, class V>
int Map<K,V>::find(const V& v) const
{
	for(int i=0;i<this->getSize();i++)
		if(this->A2[i]==v)
			return i;
	return -1;
}

template<class K, class V>
K& Map<K,V>::operator[](const V& a) const
{
	for (int i = 0; i < size; i++)
	{
		if (A2[i] == a)
			return A1[i];
	}
	assert(false);
}
template<class K, class V>
V& Map<K,V>::operator[](const K& a) const
{
	for (int i = 0; i < size; i++)
	{
		if (A1[i] == a)
			return A2[i];
	}
	assert(false);
}

template<class K, class V>
K& Map<K,V>:: keyAtIndex(const int& i) const
{
	assert(i>=0 &&i<size);
	return A1[i];
}

template<class K, class V>
V& Map<K,V>::valueAtIndex(const int& i) const
{
	assert(i>=0 &&i<size);
	return A2[i];
}


template<class K, class V>
void Map<K,V>::append(const K& a, const V& b)
{
	K* t1 = new K[size+1];
	V* t2 = new V[size+1];
	for (int i = 0; i < size; i++)
	{
		t1[i] = A1[i];
		t2[i] = A2[i];
	}
	t1[size] = a;
	t2[size] = b;
	int t = size;
	A1 = t1;
	A2 = t2;
	size = ++t;
}

template<class K, class V>
bool Map<K,V>::remove(const int& a)
{

	if(a<0 ||a>=this->getSize())
		return false;

	else
	{
		K *x = new K[this->getSize()-1];
		V*y = new V[this->getSize()-1];
		for(int i=0;i<a;i++)
		{
			x[i]=this->A1[i];
			y[i]=this->A2[i];
		}
		for(int i=a+1; i<this->getSize();i++)
		{

			x[i-1]=this->A1[i];
			y[i-1]=this->A2[i];
		}
		if(this->getSize()>0)
		{
			delete[]this->A1;
			delete[]this->A2;
		}
		this->A1=x;
		this->A2=y;
		this->size -=1;
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Course
{
private:
	string name;
	int creditHours;
public:
	Course();
	Course(const string&, const int&);
	string getCourseName() const;
	int getCreditHours() const;
	void setCourseName(const string&);
	void setCreditHours(const int&);
	bool operator == (const Course&) const; //Return true if course names are equal and credit hours are also equal.
	friend istream& operator >> (istream&, Course&);
	friend ostream& operator << (ostream&, const Course&);
};

Course::Course()
{
	name = "None";
	creditHours = 0;
}
ostream& operator << (ostream& out, const Course& c)
{
	out << "Course Name = " << c.name << ", Credit Hours = " << c.creditHours;
	return out;
}
Course::Course(const string& a,const int& h)
{
	this->name=a;
	this->creditHours=h;
}
string Course:: getCourseName()const
{
	return name;
}
int Course:: getCreditHours()const
{
	return creditHours;
}
void Course::setCourseName(const string& a)
{
	name=a;
}
void Course:: setCreditHours(const int& h)
{
	creditHours=h;
}
bool Course::operator==(const Course& a)const
{
	bool answer=1;
	if((name==a.name)&&(creditHours==a.creditHours))
		return answer;
	else
	{
		answer=0;
		return answer;
	}
}
istream& operator >> (istream& in, Course& a)
{
	in>>a.name;
	in>>a.creditHours;
	return in;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Date
{
	int d, m, y;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Student
{
private:
	string fn, ln; //first name and last name
	Date dob;
public:
	Student(); //Implemented for you
	Student(const string& firstName, const string& lastName, const Date&);
	string getFirstName() const;
	string getLastName() const;
	Date getDob() const;
	void setFirstName(const string&);
	void setLastName(const string&);
	void setDob(const Date&);
	bool operator == (const Student&) const; //Return true if all the first names, last names, and date of births are equal
	friend istream& operator >> (istream&, Student&);
	friend ostream& operator << (ostream&, const Student&); //Implemented for you
};
Student::Student()
{
	fn = "None";
	ln = "None";
	dob.y = 0;
	dob.m = 0;
	dob.d = 0;
}
ostream& operator << (ostream& out, const Student& s)
{
	out << "Full Name = " << s.fn << " " << s.ln << ": ";
	out << "DOB (d-m-y) = " << s.dob.d << "-" << s.dob.m << "-" << s.dob.y;
	return out;
}
Student::Student(const string& f,const string& l,const Date& date)
{
	fn=f;
	ln=l;
	dob.y=date.y;
	dob.m=date.m;
	dob.d=date.d;
}

string Student::getFirstName() const
{
	return fn;
}

string Student::getLastName() const
{
	return ln;
}

Date Student::getDob() const
{
	return dob;
}

void Student::setFirstName(const string&f)
{
	fn=f;
}

void Student::setLastName(const string&l)
{
	ln=l;
}

void Student::setDob(const Date& date)
{
	dob.y=date.y;
	dob.m=date.m;
	dob.d=date.d;
}

bool Student::operator == (const Student &a) const
{	
	if((fn==a.getFirstName())&&(ln==a.getLastName())&&(dob.y==a.dob.y) &&(dob.m==a.dob.m)&&(dob.d==a.dob.d))
		return true;
	else
		return false;
}

istream& operator >> (istream& in, Student& s)
{
	in>>s.fn;
	in>>s.ln;
	in>>s.dob.d;
	in>>s.dob.m;
	in>>s.dob.y;
	return in;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Map<int, char> StudentMap;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SchoolManagementSystem
{
private:
	SmarterArray<Student> studentList; //A SmarterArray to store the students in the school
	SmarterArray<Course> courseList; //A SmarterArray to store the courses in the school
	SmarterArray<StudentMap> studentMapList; //A SmarterArray to store the students' maps

public:
	SchoolManagementSystem();

	int getNumberOfRegisteredStudents() const;
	int getNumberOfCoursesOffered() const;

	int findStudent(const string& firstName, const string& lastName) const;
	Student getStudent(const int& studentIndex) const;
	StudentMap getStudentMap(const int& studentIndex) const;
	bool registerStudent(const Student& s);
	bool enrolStudent(const int& studentIndex, const int& courseIndex);
	void removeStudent(const int& studentIndex);
	bool withdrawStudent(const int& studentIndex, const int& courseIndex);
	bool assignLetterGrade(const int& studentIndex, const int& courseIndex, const char& letterGrade);
	double getStudentGPA(const int& studentIndex) const;
	int getTopStudentIndex() const;

	int findCourse(const string& courseName) const;
	Course getCourse(const int& courseIndex) const;
	bool offerCourse(const Course& course);
	void removeCourse(const int& courseIndex);

	friend ostream& operator << (ostream&, const SchoolManagementSystem&);
	static Student generateRandomStudent();
	static char generateRandomLetterGrade();
};
SchoolManagementSystem::SchoolManagementSystem()
{}
int SchoolManagementSystem::getNumberOfRegisteredStudents()const
{
	return this->studentList.getSize();
}
int SchoolManagementSystem::getNumberOfCoursesOffered()const
{
	return this->courseList.getSize();
}
int SchoolManagementSystem::findStudent(const string& firstName, const string& lastName) const
{
	int answer = -1;
	for(int i =0;i <this->studentList.getSize() ; i++)
		if(this->studentList[i].getFirstName()==firstName && this->studentList[i].getLastName()==lastName)
		{
			answer=i;
			break;
		}
	return answer;
}

Student SchoolManagementSystem::getStudent(const int& studentIndex) const
{
	assert(studentIndex>=0 && studentIndex<this->studentList.getSize());
	return this->studentList[studentIndex];
}

StudentMap SchoolManagementSystem::getStudentMap(const int& studentIndex) const
{
	assert(studentIndex>=0 && studentIndex<this->studentList.getSize());
	return this->studentMapList[studentIndex];
}

bool SchoolManagementSystem::registerStudent(const Student& s)
{
	bool answer =1;
	if(findStudent(s.getFirstName(), s.getLastName()) == -1 )
	{
		this->studentList.append(s);
		this->studentMapList.append(Map<int,char>());
		return answer;
	}
	else
	{
		answer=0;
		return answer;
	}

}
bool SchoolManagementSystem::enrolStudent(const int& studentIndex, const int& courseIndex)
{
	if(studentMapList[studentIndex].find(courseIndex)==-1)
	{
		this->studentMapList[studentIndex].append(courseIndex,'N');
        return true;
	}
	else
	return false;
}

void SchoolManagementSystem::removeStudent(const int& studentIndex)
{
	assert(studentIndex>=0 && studentIndex<this->studentList.getSize());
	studentList.remove(studentIndex);
	studentMapList.remove(studentIndex);

}
bool SchoolManagementSystem::withdrawStudent(const int& studentIndex, const int& courseIndex)
{
	bool answer = 0;
	assert(studentIndex>=0 && studentIndex<this->studentList.getSize());
	assert(courseIndex>=0 && courseIndex<this->courseList.getSize());

	if(this->studentMapList[studentIndex].find(courseIndex)!=-1)
	{
		this->studentMapList[studentIndex].remove(courseIndex);
		return 1;
	}
	return answer;
}

bool SchoolManagementSystem::assignLetterGrade(const int& studentIndex, const int& courseIndex, const char& letterGrade)
{
	bool answer=0;
	assert(studentIndex>=0 && studentIndex<this->studentList.getSize());
	assert(courseIndex>=0 && courseIndex<this->courseList.getSize());
	assert(letterGrade=='A' || letterGrade=='B' || letterGrade=='C' || letterGrade=='D' || letterGrade=='F');


	for(int i=0;i<this->studentMapList[studentIndex].getSize();i++)
		if(courseIndex == this->studentMapList[studentIndex].keyAtIndex(i))
		{
			studentMapList[studentIndex].valueAtIndex(i) = letterGrade;
			answer= 1;
			break;
		}

	return answer;
}

double SchoolManagementSystem::getStudentGPA(const int& studentIndex) const
{
	if(studentIndex>=0 && studentIndex<studentMapList.getSize())
	{
		double a = 0;
		int sum = 0;
		StudentMap temp(studentMapList[studentIndex]);
		for(int i=0;i<temp.getSize();i++)
		{
			int hours = courseList[temp.keyAtIndex(i)].getCreditHours();
			switch(temp.valueAtIndex(i))
			{
			case 'A':a+=hours*4;sum=sum+4; break;
			case 'B':a+=hours*3;sum=sum+3; break;
			case 'C':a+=hours*2;sum=sum+2; break;
			case 'D':a+=hours*1;sum=sum+1; break;
			default: a+=0; break;
			}
		}
		if(sum==0)
			return 0;
		else
			return a/sum;
	}
	else
		return 0;
}

int SchoolManagementSystem::getTopStudentIndex() const
{

	int a = -1;
	double b = -1;
	for(int i=0;i<studentList.getSize();i++)
	{
		if(b<getStudentGPA(i))
		{
			b = getStudentGPA(i);
			a=i;
		}
	}
	return a;
}

int SchoolManagementSystem::findCourse(const string& courseName) const
{
	int answer=-1;
	for(int k=0;k<courseList.getSize();k++)
	{
		if( courseList[k].getCourseName() == courseName )
			answer = k;
	}
	return answer;
}
Course SchoolManagementSystem::getCourse(const int& courseIndex) const
{
	assert(courseIndex>=0 && courseIndex<courseList.getSize());
	return courseList[courseIndex];
}

bool SchoolManagementSystem::offerCourse(const Course& course)
{
	bool answer=true;
	for(int k=0;k<courseList.getSize();k++)
	{
		if(courseList[k]==course)
		{
			answer=false;
			break;
		}
	}
	if(answer)
		courseList.append(course);

	return answer;
}

void SchoolManagementSystem::removeCourse(const int& courseIndex)
{
	assert(courseIndex>=0 && courseIndex<courseList.getSize());

	courseList.remove(courseIndex);

	for(int k=0;k<studentList.getSize();k++)
	{
		StudentMap temp_map(this->studentMapList[k]);
		for(int i=0;i<temp_map.getSize();i++)
		{
			if(temp_map.keyAtIndex(i)==courseIndex)
			{
				temp_map.remove(i);
			}
		}
	}

}
ostream& operator << (ostream& out, const SchoolManagementSystem& sms)
{
	out << endl << "Students List" << endl;
	if (sms.studentList.getSize() == 0)
		out << "No student has been registered yet." << endl;
	for (int studentIndex = 0; studentIndex < sms.studentList.getSize(); studentIndex++)
		out << "Student at index " << studentIndex << ": " << sms.studentList[studentIndex] << endl;

	out << endl << "Courses List" << endl;
	if (sms.courseList.getSize() == 0)
		out << "No course has been offered yet." << endl;
	for (int courseIndex = 0; courseIndex < sms.courseList.getSize(); courseIndex++)
		out << "Course at index " << courseIndex << ": " << sms.courseList[courseIndex] << endl;

	cout << endl << "Students Map" << endl;
	if (sms.studentMapList.getSize() == 0)
		out << "No student is enrolled in any course yet." << endl;
	for (int studentIndex = 0; studentIndex < sms.studentMapList.getSize(); studentIndex++)
	{
		out << "Student at index " << studentIndex << endl;
		out << sms.studentMapList[studentIndex];
		out << "GPA = " << sms.getStudentGPA(studentIndex) << endl << endl;
	}
	return out;
}
Student SchoolManagementSystem::generateRandomStudent()
{
	string fn, ln;
	Date dob;

	fn = rand() % 26 + 65;
	for (int i = 0; i < 9; i++)
		fn += char(rand() % 26 + 97);

	ln = rand() % 26 + 65;
	for (int i = 0; i < 9; i++)
		ln += char(rand() % 26 + 97);

	dob.y = 1998 + rand() % 5;
	dob.m = 1 + rand() % 12;
	dob.d = 1 + rand() % 30;

	return Student(fn, ln, dob);
}
char SchoolManagementSystem::generateRandomLetterGrade()
{
	int g = rand() % 11;
	if (g == 0)
		return 'A';
	else if (g <= 2)
		return 'B';
	else if (g <= 5)
		return 'C';
	else if (g <= 7)
		return 'D';
	else
		return 'F';
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	cout << "Welcome to Phantom College School Management System" << endl;
	cout << "===================================================" << endl;

	srand(1);

	//Prepare the courses offered in the school
	Course course[] = {Course("CMPT120", 2), Course("CMPT130", 3), Course("CMPT135", 4),
				  Course("MACM101", 2), Course("CALC151", 3), Course("CALC152", 4),
				  Course("MATH242", 4), Course("ECON101", 3), Course("ECON102", 4),
				  Course("ENGL100", 2), Course("HIST101", 3), Course("PHYS100", 2),
				  Course("PHYS101", 3), Course("PHYS102", 4), Course("CHEM101", 3),
				  Course("CHEM102", 4)};

	//Construct a school management system object
	SchoolManagementSystem sms;
	cout << sms << endl;

	//Register some new students
	for (int i = 0; i < 10; i++)
	{
		bool flag = sms.registerStudent(Student(sms.generateRandomStudent()));
		if (flag)
			cout <<"Student registration successful." << endl;
		else
			cout << "Student registration failed. The same student already exists in the system." << endl;
	}
	cout << endl << "Some students have been registered in to the system." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;

	//See if Yonas Weldeselassie is a student in the school
	int studentIndex = sms.findStudent("Yonas", "Weldeselassie");
	if (studentIndex == -1)
		cout << "Yonas Weldeselassie is not a student in the school." << endl << endl;
	else
	{
		cout << "Yonas Weldeselassie is a student in the school. Details below..." << endl;
		cout << sms.getStudent(studentIndex) << endl;
		cout << sms.getStudentMap(studentIndex) << endl;
	}

	//See if a randomly chosen student among those existing students is a student in the school
	int randomStudentIndex = rand() % sms.getNumberOfRegisteredStudents();
	Student s = sms.getStudent(randomStudentIndex);
	studentIndex = sms.findStudent(s.getFirstName(), s.getLastName());
	if (studentIndex == -1)
		cout << s.getFirstName() << " " << s.getLastName() << " is not a student in the school." << endl << endl;
	else
	{
		cout << s.getFirstName() << " " << s.getLastName() << " is a student in the school. Details below..." << endl;
		cout << sms.getStudent(studentIndex) << endl;
		cout << sms.getStudentMap(studentIndex);
		cout << "GPA = " << sms.getStudentGPA(studentIndex) << endl;
	}

	//Add courses offered to the system
	for (int i = 0; i < 16; i++)	//there are 16 courses initially
	{
		bool flag = sms.offerCourse(course[i]);
		if (flag)
			cout <<"Course offering successful." << endl;
		else
			cout << "Course offering failed. The same course already exists in the system." << endl;
	}
	cout << endl << "Some courses have been offered and added in to the system." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;

	//See if CMPT135 course is offered in the school
	int courseIndex = sms.findCourse("CMPT225");
	if (courseIndex == -1)
		cout << "CMPT225 course is not offered in the school." << endl << endl;
	else
	{
		cout << "CMPT225 course is offered in the school. Details below..." << endl;
		cout << sms.getCourse(courseIndex) << endl;
	}

	//See if a randomly chosen student among those existing students is a student in the school
	int randomCourseIndex = rand() % sms.getNumberOfCoursesOffered();
	Course c = sms.getCourse(randomCourseIndex);
	courseIndex = sms.findCourse(c.getCourseName());
	if (courseIndex == -1)
		cout << c.getCourseName() << " course is not offered in the school." << endl << endl;
	else
	{
		cout << c.getCourseName() << " course is offered in the school. Details below..." << endl;
		cout << sms.getCourse(courseIndex) << endl;
	}

	//Enroll students to some courses
	for (int studentIndex = 0; studentIndex < sms.getNumberOfRegisteredStudents(); studentIndex++)
	{
		int numberOfCourses = rand() % (sms.getNumberOfCoursesOffered()/2);
		for (int i = 0; i < numberOfCourses; i++)
		{
			int courseIndex = rand() % sms.getNumberOfCoursesOffered();
			sms.enrolStudent(studentIndex, courseIndex);
		}
	}
	cout << endl << "Some students have been enrolled in to some courses." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;

	//remove the randomly chosen student among those existing students is a student in the school
	randomStudentIndex = rand() % sms.getNumberOfRegisteredStudents();
	sms.removeStudent(randomStudentIndex);
	cout << endl << "The student at index " << randomStudentIndex << " has been removed from the system." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;

	//Assign letter grades to the students
	for (int studentIndex = 0; studentIndex < sms.getNumberOfRegisteredStudents(); studentIndex++)
	{
		int n = sms.getStudentMap(studentIndex).getSize(); //Assign letter grades to each course the student is enrolled in
		for (int j = 0; j < n; j++)
		{
			int courseIndex = sms.getStudentMap(studentIndex).keyAtIndex(j);
			sms.assignLetterGrade(studentIndex, courseIndex, sms.generateRandomLetterGrade());
		}
	}
	cout << endl << "Students have been assigned letter grades." << endl;
	cout << "The updated system information is..." << endl;
	cout << sms << endl;

	//Withdraw a student from a course
	randomStudentIndex = rand() % sms.getNumberOfRegisteredStudents();
	s = sms.getStudent(randomStudentIndex);
	studentIndex = sms.findStudent(s.getFirstName(), s.getLastName());
	if (studentIndex == -1)
		cout << s.getFirstName() << " " << s.getLastName() << " is not a student in the school." << endl << endl;
	else
	{
		cout << s.getFirstName() << " " << s.getLastName() << " is a student in the school. Details below..." << endl;
		cout << sms.getStudent(studentIndex) << endl;
		cout << sms.getStudentMap(studentIndex) << endl;
		int randomCourseMapIndex = rand() % sms.getStudentMap(studentIndex).getSize();
		int courseIndex = sms.getStudentMap(studentIndex).keyAtIndex(randomCourseMapIndex);
		bool flag = sms.withdrawStudent(studentIndex, courseIndex);
		if (!flag)
			cout << "Withdrawing the student at index " << studentIndex << " from the course at index " << courseIndex << " failed." << endl << endl;
		else
		{
			cout << "Student at index " << studentIndex << " withdrawn from the course at index " << courseIndex << endl;
			cout << "The updated information for the student is now..." << endl;
			cout << sms.getStudent(studentIndex) << endl;
			cout << sms.getStudentMap(studentIndex) << endl;
		}
	}
	
	//Compute and print the top student
	int topStudentIndex = sms.getTopStudentIndex();
	cout << "The top student is..." << endl;
	cout << sms.getStudent(topStudentIndex) << endl;
	cout << "GPA = " << sms.getStudentGPA(topStudentIndex) << endl << endl;

	//Remove the course at index 10
	courseIndex = 10;
	c = sms.getCourse(courseIndex);
	sms.removeCourse(courseIndex);
	cout << c.getCourseName() << " has been removed from the system." << endl;
	cout << "The system has been updated. Below is the updated system information..." << endl;
	cout << sms << endl;

	system("Pause");
	return 0;
}
