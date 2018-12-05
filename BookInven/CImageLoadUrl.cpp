#include "CImageLoadUrl.h"



CImageLoadUrl::CImageLoadUrl()
{
}


CImageLoadUrl::~CImageLoadUrl()
{
}

//curl writefunction to be passed as a parameter
// we can't ever expect to get the whole image in one piece,
// every router / hub is entitled to fragment it into parts
// (like 1-8k at a time),
// so insert the part at the end of our stream.
size_t CImageLoadUrl::write_data(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	std::vector<uchar> *stream = (std::vector<uchar>*)userdata;
	size_t count = size * nmemb;
	stream->insert(stream->end(), ptr, ptr + count);
	return count;
}

//function to retrieve the image as cv::Mat data type
cv::Mat CImageLoadUrl::Load(const char *img_url, int timeout)
{
	std::vector<uchar> stream;
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, img_url); //the img url
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); // pass the writefunction
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream); // pass the stream ptr to the writefunction
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); // timeout if curl_easy hangs, 
	CURLcode res = curl_easy_perform(curl); // start curl
	curl_easy_cleanup(curl); // cleanup

	return cv::imdecode(stream, -1); // 'keep-as-is'
}