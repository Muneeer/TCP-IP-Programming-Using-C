



in_addr_t get_host_addr(const char *name, int idx)
{
	struct hostent *host;
	host=gethostbyname(name);
	  if(!host)
  	{
  		exit(1); 
  	}
  	if(host->h_addr_list[idx]==NULL)
  		host->h_addr_list[idx]=INADDR_NONE;
  	
  	return host->h_addr_list[idx];
}
char *get_host_name(const char *addr)
{
	struct hostent *host;
	struct in_addr addrr;
	inet_aton(addr,&addrr);
	host=gethostbyaddr(&addrr,sizeof(addrr), AF_INET);
  
  	if(!host)
  	{
  		error_handling("gethost.... error");
 	 }
  	
  	return (char *)host->h_name;
	
}

int is_official_name(const char *name)
{
	struct hostent *host;
	host=gethostbyname(name);
	
	if(!host)
  	{
  		return -1;
  	}
  	if(host->h_name==name)
  		return 1;
  	else
  		return 0;
}
