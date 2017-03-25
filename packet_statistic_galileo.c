#include <pcap.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>

#define DEV "wlp1s0"

#define ETH_HDR 14
#define TCP_HDR 20
#define IP_HDR 20

#define OFFSET 23
#define UDP_PROTOCOL 0x11
#define TCP_PROTOCOL 0x06

using namespace std;

long starttime;
map <long, long> stat_data_persec;
map <long, long> stat_data_per100ms;

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

  
	long sectime = pkthdr->ts.tv_sec - starttime;
	long mstime = sectime * 100 + (pkthdr->ts.tv_usec / 100000);
	stat_data_persec[sectime] += pkthdr->len;
	stat_data_per100ms[mstime] += pkthdr->len;
	return;

}

void dump_data() {
	FILE *fp;
	fp = fopen("/media/realroot/packetstat/packet_stat_persec.txt", "w+");
	map <long, long>::iterator iter;
	for (iter = stat_data_persec.begin(); iter != stat_data_persec.end(); iter++) {
		fprintf(fp, "%ld,%ld\n", iter->first, iter->second);
	}
	fclose(fp);

	fp = fopen("/media/realroot/packetstat/packet_stat_per100ms.txt", "w+");
	for (iter = stat_data_per100ms.begin(); iter != stat_data_per100ms.end(); iter++) {
		fprintf(fp, "%ld,%ld\n", iter->first, iter->second);
	}
	fclose(fp);
}

int main(int argc,char *argv[])
{
  struct timeval tv; 
  char errBuf[PCAP_ERRBUF_SIZE], * devStr;
  /* open a device, wait until a packet arrives */
  pcap_t * device = pcap_open_live(DEV, ETH_HDR+TCP_HDR+IP_HDR+BUNDLE_HDR+20, 0, 0, errBuf);

  if(!device)
  {
    printf("error: pcap_open_live(): %s\n", errBuf);
    exit(1);
  }

  gettimeofday(&tv, NULL);
  starttime = tv.tv_sec;

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
