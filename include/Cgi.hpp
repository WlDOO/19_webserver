#pragma once
#include <iostream>

class Cgi {

	private :

		std::string _Post_cgi_FN;
		std::string _Post_cgi_LN;
		std::string _Post_cgi_content_type;
		std::string _Post_cgi_content_lenght;

	public :

		Cgi();
		~Cgi();

		int			cgi_handle(std::string const &Request_type, std::string const &Script, std::string const &Script_path, std::string &_Cgi_output);
		int			cgi_parse(std::string output, std::string &_Cgi_output);
		void		Set_fn(std::string fn);
		void		Set_ln(std::string ln);
		void		Set_content_type(std::string content_type);
		void		Set_content_lenght(std::string content_lenght);
};