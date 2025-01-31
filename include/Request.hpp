/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:39:29 by jihoolee          #+#    #+#             */
/*   Updated: 2022/06/15 14:54:24 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP_
# define REQUEST_HPP_

# include <sys/time.h>
# include <string>
# include <map>
# include <set>

class LocationConfig;
class Connection;
class ServerConfig;

class Request {
 public:
  enum Phase { READY, ON_HEADER, ON_BODY, COMPLETE };
  enum Method { DEFAULT, HEAD, GET, POST, PUT, DELETE };
  enum URIType { DIRECTORY, FILE, FILE_TO_CREATE, CGI };
  enum TransferType { GENERAL, CHUNKED };

  Request(void);
  Request(Connection* connection, ServerConfig* serverconfig, std::string start_line);
  Request(const Request& r);

  Request& operator=(const Request& ref);

  ~Request(void);

  /* getter function */
  Connection *get_m_connection() const;
	LocationConfig *get_m_locationconfig() const;
  Phase get_m_phase() const;
  Method get_m_method() const;
  URIType get_m_uri_type() const;
  TransferType get_m_transfer_type() const;
  const std::string &get_m_uri() const;
  const std::string &get_m_protocol() const;
  const std::map<std::string, std::string>& get_m_headers() const;
  int get_m_special_header_count() const;
  const std::string &get_m_query() const;
  const std::string &get_m_content() const;
  int get_m_content_length() const;
  timeval& get_m_start_at();
  const std::string &get_m_path_translated() const;
  const std::string &get_m_script_translated() const;
  const std::string &get_m_path_info() const;
	std::string get_m_method_to_string() const;

  /* setter function */
  void set_m_phase(Phase phase);
  void set_m_method(Method method);
  void set_m_uri_type(URIType uritype);
  void set_m_transfer_type(TransferType transfertype);
  void set_m_uri(std::string uri);
  void set_m_protocol(std::string protocol);
  void set_m_headers(std::map<std::string, std::string> headers);
  void set_m_content(std::string content);
  void set_m_content_length(int content_length);
  bool ParseMethod(std::string method);
  void AddContent(std::string added_content);
  bool AssignLocationMatchingUri(std::string uri);
  void clear();

  /* member function */
  std::string ParseUri();
  std::string GetTranslatedPath(std::string root, std::string uri);
  std::string GetIndexPath(const std::set<std::string>& index_set, std::string base_path);
  void AddHeader(std::string header);


 private:
  ServerConfig*                       m_server_config_;
  Connection*                         m_connection_;
  LocationConfig*                     m_locationconfig_;
  timeval                             m_start_at_;
  Phase                               m_phase_;
  Method                              m_method_;
  std::string                         m_content_;
  int                                 m_content_length_;
  URIType                             m_uri_type_;
  TransferType                        m_transfer_type_;
  std::string                         m_uri_;
  std::string                         m_protocol_;
  std::map<std::string, std::string>  m_headers_;
  int                                 m_special_header_count_;
  std::string                         m_query_;
  std::string                         m_script_translated_;
  std::string                         m_path_translated_;
  std::string                         m_path_info_;
};  //  class Request

#endif  //  REQUEST_HPP_
