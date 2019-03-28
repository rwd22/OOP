
#include "json.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

std::string get_right_of_delim(std::string const& str, std::string const& delim){
  return str.substr(str.find(delim) + delim.size());
}


int
main()
{
  /*std::istreambuf_iterator<char> first(std::cin);
  std::istreambuf_iterator<char> last;
  std::string s(first, last);  

  json::Value* v = json::parse(s);

  // std::cout << v << '\n';
  std::cout << size(*v) << '\n';
  std::cout << height(*v) << '\n';*/
  
  std::string filename;
  
  bool check = false;
  
  std::cout << "Please input json filename" << std::endl;
  std::cin >> filename;
  
  std::ifstream jfile(filename);
  std::string   line;
  
  std::vector<json::Post> posts;
  
  if(jfile)
  {
		std::string title;
		std::string author;
		std::string test;
		
		std::getline (jfile, test);
		
		json::Post reddit;
		
		int i = 1;
		
		while(test.find("\"author_fullname\": \"") != std::string::npos)
		{
			test = get_right_of_delim(test, "\"author_fullname\": \"");
		
			author = test.substr(0, test.find("\","));
			
			test = get_right_of_delim(test, "\"title\": \"");
			
			title = test.substr(0, test.find("\","));
			
			reddit.Title = title;
			
			reddit.Author = author;
		
			posts.push_back(reddit);
			
		
		}
		
		for (std::vector<json::Post>::const_iterator i = posts.begin(); i != posts.end(); ++i)
			std::cout << *i << std::endl;
		
		

  }
  else
  {
	  std::cout << "File Not Found" << std::endl;
  }
  
  
  return 0;
}
