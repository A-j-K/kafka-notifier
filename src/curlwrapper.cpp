
#include "curlwrapper.hpp" 

int CurlWrapper::is_init = 0;

CurlWrapper::CurlWrapper()
{
	if(CurlWrapper::is_init == 0) {
		CurlWrapper::is_init++;
		curl_global_init(CURL_GLOBAL_ALL);	
	}
	_pcurl = curl_easy_init();
	_pheaders = NULL;
}

CurlWrapper::~CurlWrapper()
{
	curl_easy_cleanup(_pcurl);
	if(_pheaders) {
		curl_slist_free_all(_pheaders);
		_pheaders = NULL;
	}
	CurlWrapper::is_init--;
	if(CurlWrapper::is_init == 0) {
		curl_global_cleanup();
	}
}

