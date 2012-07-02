/**

	Copyright (c) 2012, C2Serve (http://www.c2serve.eu)
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. All advertising materials mentioning features or use of this software
	   must display the following acknowledgement: "This product includes software of the C2Serve project".
	4. Neither the name of the C2Serve project nor the
	   names of its contributors may be used to endorse or promote products
	   derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY C2SERVE ''AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL C2SERVE BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#include "C2SHttpClient.h"
#include "C2SHttpRequest.h"

#include <iostream>

const std::string sExampleServerHostName = "localhost";
const unsigned short iExampleServerPort = 3456;

const std::string sExampleServerRESTResourceContextRoot = "/c2s-example/";
const std::string sExampleServerSayHelloMethodPath = "say-hello/to";
const std::string sNameToGreet = "C2SExampleClient";

int main( int , char ** )
{
  using namespace c2s;
  C2SHttpClient clientToAccessExampleServer( sExampleServerHostName , iExampleServerPort );
  std::string sPathToSayHelloMethodOfExampleServer = sExampleServerRESTResourceContextRoot + sExampleServerSayHelloMethodPath;
  sPathToSayHelloMethodOfExampleServer += "/" + sNameToGreet;
  C2SHttpRequestHeader requestHeaderToAccessSayHelloMethodOfExampleServer( C2S_GET , sPathToSayHelloMethodOfExampleServer );
  requestHeaderToAccessSayHelloMethodOfExampleServer.Fields.addAccept( C2SHttpMediaType::wildcard );
  C2SHttpRequest requestToAccessSayHelloMethodOfExampleServer( requestHeaderToAccessSayHelloMethodOfExampleServer );
  C2SHttpResponse *pResponseOfExampleServer = clientToAccessExampleServer.send( requestToAccessSayHelloMethodOfExampleServer );
  if ( pResponseOfExampleServer->header().Status != OK )
    std::cerr << "Invalid server response: " << pResponseOfExampleServer->header().Status << " " << pResponseOfExampleServer->header().ReasonPhrase << std::endl;
  else
  {
    std::cout << "Server response:" << pResponseOfExampleServer->header().Status << " " << pResponseOfExampleServer->header().ReasonPhrase << std::endl;
    std::string sReceivedResponseEntity;
    pResponseOfExampleServer->getEntity( &sReceivedResponseEntity );
    std::cout << sReceivedResponseEntity << std::endl;
  }

  delete pResponseOfExampleServer;

  return 0;
}
