#pragma once

#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <curl/curl.h>

struct CurlBodyHolder;
struct CurlHeaderHolder;

typedef size_t (*curlwrapper_callback)(char*,size_t,size_t,void*);

class CurlWrapper
{
public:
	typedef std::shared_ptr<CurlWrapper> ShPtr;

	CurlWrapper();
	virtual ~CurlWrapper();

	virtual void
	setHeader(const std::string &header) {
		setHeader(header.c_str());
	}

	virtual void
	setHeader(const char *p) {
		_pheaders = curl_slist_append(_pheaders, p); 
	}

	virtual void
	setWriteFunction(curlwrapper_callback cb) {
		curl_easy_setopt(_pcurl, CURLOPT_WRITEFUNCTION, cb);
	}

	virtual void
	setWriteData(void *p) {
		curl_easy_setopt(_pcurl, CURLOPT_WRITEDATA, p);
	}
	
	virtual void
	setHeaderFunction(curlwrapper_callback cb) {
		curl_easy_setopt(_pcurl, CURLOPT_HEADERFUNCTION, cb);
	}

	virtual void
	setHeaderData(void *p) {
		curl_easy_setopt(_pcurl, CURLOPT_HEADERDATA, p);
	}
	
	virtual void
	setData(void *p, long len) {
		curl_easy_setopt(_pcurl, CURLOPT_POSTFIELDSIZE, len);
		curl_easy_setopt(_pcurl, CURLOPT_COPYPOSTFIELDS, p);
	}

	virtual void
	setUrl(const std::string &s) {
		curl_easy_setopt(_pcurl, CURLOPT_URL, s.c_str());
	}

	virtual void
	setUrl(const char *s) {
		curl_easy_setopt(_pcurl, CURLOPT_URL, s);
	}

	virtual void 
	setCustomRequest(const char *p) {
		curl_easy_setopt(_pcurl, CURLOPT_CUSTOMREQUEST, p);
	}

	virtual void 
	setCustomRequest(const std::string &s) {
		setCustomRequest(s.c_str());
	}

	virtual void 
	setVerb(const std::string &s) {
		setCustomRequest(s.c_str());
	}

	virtual void 
	setVerb(const char *p) {
		setCustomRequest(p);
	}

	virtual void
	setUsername(const char *p) {
		curl_easy_setopt(_pcurl, CURLOPT_USERNAME, (char*)p);
	}

	virtual void
	setUsername(const std::string &s) {
		setUsername(s.c_str());
	}

	virtual void
	setPassword(const char *p) {
		curl_easy_setopt(_pcurl, CURLOPT_PASSWORD, (char*)p);
	}

	virtual void
	setPassword(const std::string &s) {
		setPassword(s.c_str());
	}

	virtual void
	recycle() {
        	curl_easy_setopt(_pcurl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(_pcurl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(_pcurl, CURLOPT_VERBOSE, 0L);
		curl_easy_setopt(_pcurl, CURLOPT_FOLLOWLOCATION, 0L);
		curl_easy_setopt(_pcurl, CURLOPT_MAXREDIRS, 0L);
		if(_pheaders) {
			curl_slist_free_all(_pheaders);
			_pheaders = NULL;
		}
	}

	virtual CURLcode
	perform(void) {
		CURLcode rval;
		curl_easy_setopt(_pcurl, CURLOPT_HTTPHEADER, _pheaders);
		rval = curl_easy_perform(_pcurl);
		curl_slist_free_all(_pheaders);
		_pheaders = NULL;
		return rval;
	}

	static int is_init;

protected:

	CURL		*_pcurl;
	curl_slist 	*_pheaders;
	CurlBody	*_preturnbody;
	CurlHeader	*_preturnheader;
};


struct CurlHeader
{
	typedef std::shared_ptr<CurlHeaderHolder> ShPtr;
	typedef std::vector<std::string> HeaderVec;
	HeaderVec _headers;
	void addHeader(char *in, size_t len) {
		if(len > 0) {
			std::string s;
			s.append(in, len);
			_headers.push_back(s);
		}
	}
	void dumpToStream(std::ostream *pstream) {
		HeaderVec::iterator itor = _headers.begin();
		while(itor != _headers.end()) {
			(*pstream) << *itor;
			itor++;
		}
	}
	std::string getHeader(int idx) { 
		return _headers[idx];
	}
	bool isEmpty() {
		return _headers.empty();
	}
};

struct CurlBody
{
	typedef std::shared_ptr<CurlBodyHolder> ShPtr;
	std::stringstream _oss;
	CurlBody() {}
	void addBuffer(char *pbuf, size_t len) {
		if(len > 0) {
			_oss.write(pbuf,len);
		}
	}
	void dumpToStream(std::ostream *pstream) {
		(*pstream) << _oss.str();
	}
	std::stringstream& getStream() { return _oss; }
};



