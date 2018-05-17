
#include <string>
#include <vector>
#include <iostream> // for std::cout
#include <memory>
#include <sstream>
#include <curl/curl.h>

struct HeaderHolder
{
public:
	typedef std::shared_ptr<HeaderHolder> ShPtr;
	typedef std::vector<std::string> HeaderVec;
	HeaderVec _headers;
	void addHeader(char *in, size_t len) {
		std::string s;
		s.append(in, len);
		_headers.push_back(s);
	}
};

struct BodyHolder
{
public:
	typedef std::shared_ptr<BodyHolder> ShPtr;
	typedef std::shared_ptr<std::stringstream> SteamShPtr;
	SteamShPtr _poss;
	BodyHolder() { _poss = SteamShPtr(new std::stringstream); }
	void addBody(char *in, size_t len) {
		_poss->write(in,len);
	}
	SteamShPtr getStream() { return _poss; }
};

#ifdef __cplusplus
extern "C" {
#endif
static size_t
callback_header_writer(char* pbuffer, size_t size, size_t nitems, void* puserdata)
{
	size_t actualsize = size * nitems; 
	HeaderHolder *h = (HeaderHolder*)puserdata;
	h->addHeader(pbuffer, actualsize);
	return actualsize;
}
static size_t
callback_body_writer(char* pbuffer, size_t size, size_t nitems, void* puserdata)
{
	size_t actualsize = size * nitems; 
	BodyHolder *b = (BodyHolder*)puserdata;
	b->addBody(pbuffer, actualsize);
	return actualsize;
}
#ifdef __cplusplus
} 
#endif

int main(int argc, char *argv[])
{
	size_t pos;
	int keep = 7, post = true;
	const char teststr[] = "{ \"foobarbaz\": \"alice\" }";
	std::string topic("topic.foo.bar");
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *pCurl = curl_easy_init();
	curl_easy_setopt(pCurl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(pCurl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 0L);
	while(keep) {
		curl_slist *pheaders = NULL;
		CURLcode result; 
		BodyHolder::ShPtr spBody(new BodyHolder);
		HeaderHolder::ShPtr spHeader(new HeaderHolder);
		curl_easy_setopt(pCurl, CURLOPT_URL, "http://10.211.55.13:8080");
		if(post) {
			curl_easy_setopt(pCurl, CURLOPT_CUSTOMREQUEST, "POST");
			//curl_easy_setopt(pCurl, CURLOPT_CUSTOMREQUEST, "DELETE");
			curl_easy_setopt(pCurl, CURLOPT_POSTFIELDSIZE, sizeof(teststr)-1);
			curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, teststr);
		}
		else {
			curl_easy_setopt(pCurl, CURLOPT_CUSTOMREQUEST, "PUT");
			curl_easy_setopt(pCurl, CURLOPT_POSTFIELDSIZE, sizeof(teststr)-1);
			curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, teststr);
		}
		pheaders = curl_slist_append(pheaders, "Content-Type: application/octet-stream");
		pheaders = curl_slist_append(pheaders, "Connection: keep-alive");
		pheaders = curl_slist_append(pheaders, "User-Agent: Kafka-Notifier-0.1.0");
		pheaders = curl_slist_append(pheaders, "Accept:");
		pos = topic.find("topic.", 0);
		if(pos != std::string::npos && pos == 0) {
			std::stringstream oss;
                        std::string newtopic = topic.substr(sizeof("topic.")-1);
			oss << "X-Test: " << newtopic;
			pheaders = curl_slist_append(pheaders, oss.str().c_str());
                }
		curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pheaders);
		curl_easy_setopt(pCurl, CURLOPT_USERNAME, "username-here");
		curl_easy_setopt(pCurl, CURLOPT_PASSWORD, "password-here");
		curl_easy_setopt(pCurl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, callback_body_writer);
		curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)spBody.get());
		curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, callback_header_writer);
		curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, (void*)spHeader.get());
		curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 5L);
		curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 0L);
		curl_easy_setopt(pCurl, CURLOPT_MAXREDIRS, 0L);
		result = curl_easy_perform(pCurl);

		HeaderHolder::HeaderVec::iterator itor = spHeader->_headers.begin();
		while(itor != spHeader->_headers.end()) {
			std::cout << *itor;
			itor++;
		}	
		std::cout << spBody->_poss->str();
		if(pheaders) {
			curl_slist_free_all(pheaders);
		}
		keep--;	
	}
	curl_easy_cleanup(pCurl);
	curl_global_cleanup();
	return 0;
}

