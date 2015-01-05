#include <pcap.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>

#define DEV "adhoc0"

#define ETH_HDR 14
#define TCP_HDR 20
#define IP_HDR 20
#ifdef DTN
	#define BUNDLE_HDR 120
#else
	#define BUNDLE_HDR 0
#endif
#define OFFSET 23
#define UDP_PROTOCOL 0x11
#define TCP_PROTOCOL 0x06

using namespace std;

map <long, long> stat_overload;
map <long, long> stat_payload;

void getPacket(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet)
{
 /* int * id = (int *)arg;
  printf("id: %d\n", ++(*id));
  printf("Packet length: %d\n", pkthdr->len);
  printf("Number of bytes: %d\n", pkthdr->caplen);
  printf("Recieved time: %s", ctime((const time_t *)&pkthdr->ts.tv_sec)); 
  printf("Recieved time: %d\n", pkthdr->ts.tv_sec); */
//pkthdr->ts.tv_usec;        /* microseconds */
/*  int i;
  for(i=0; i<pkthdr->len; ++i)
  {
    printf(" %02x", packet[i]);
    if( (i + 1) % 16 == 0 )
    {
      printf("\n");
    }
  }
  printf("\n\n");*/

  /*OVERLOAD*/
  if (packet[OFFSET] == UDP_PROTOCOL) {
  	stat_overload[pkthdr->ts.tv_sec] += pkthdr->len;
	return;
  }
  /*PAYLOAD*/
  if (packet[OFFSET] == TCP_PROTOCOL) {
  	long tmp = 0;
	long tmp_overload = ETH_HDR + TCP_HDR + IP_HDR + BUNDLE_HDR;
	tmp += pkthdr->len;
	tmp -= tmp_overload;
	if (tmp < 0)
		tmp += BUNDLE_HDR;
	if (tmp < 0)
		tmp = 0;
	stat_overload[pkthdr->ts.tv_sec] += tmp_overload;
	stat_payload[pkthdr->ts.tv_sec] += tmp;
	return;
  }
}

void dump_data() {
	FILE *fp;
	fp = fopen("/sdcard/packet_stat.txt", "w+");
	map <long, long>::iterator iter;
	fprintf(fp, "**************************overload****************************\n");
	for (iter = stat_overload.begin(); iter != stat_overload.end(); iter++) {
		fprintf(fp, "%ld,%ld\n", iter->first, iter->second);
	}
	fprintf(fp, "**************************payload****************************\n");
	for (iter = stat_payload.begin(); iter != stat_payload.end(); iter++) {
		fprintf(fp, "%ld,%ld\n", iter->first, iter->second);
	}
	fclose(fp);
}

int main(int argc,char *argv[])
{
  char errBuf[PCAP_ERRBUF_SIZE], * devStr;
  /* open a device, wait until a packet arrives */
  pcap_t * device = pcap_open_live(DEV, ETH_HDR+TCP_HDR+IP_HDR+BUNDLE_HDR+20, 0, 0, errBuf);

  if(!device)
  {
    printf("error: pcap_open_live(): %s\n", errBuf);
    exit(1);
  }

  /*get mac address*/
  char * str = (char *)malloc (100);
  char * tmp = (char *)malloc (20);
  strcat(str, "ether src ");

  FILE *fp;
  char addr_location[30];
  sprintf(addr_location, "%s%s%s", "sys/class/net/", DEV, "/address");
  fp = fopen(addr_location, "r");
  fscanf(fp,"%s",tmp); 
  fclose(fp);
  strcat(str, tmp);
  printf("%s\n", str);

  struct bpf_program filter;
  pcap_compile(device, &filter, str, 1, 0);
  pcap_setfilter(device, &filter);
  /* wait loop forever */
  int id = 0;
  pcap_loop(device, -1, getPacket, (u_char*)&id);
  
  dump_data();
  pcap_close(device);

  return 0;
}
