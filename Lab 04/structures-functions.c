// Cum obțin pointer la headerul de IP
struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));

// Cum trec de la _32 din IP header la in_addr?
struct in_addr adresa;
adresa.s_addr = ip_hdr->daddr;

// O intrare în tabela de ARP/Vecini
struct nei_entry {
  uint16_t proto;
  struct in_addr ip;
  struct in6_addr ip6;
  uint8_t mac[6];
};

// O intrare în tabela de rutare
struct rtable_entry {
  uint16_t proto;

  struct in_addr network;
  struct in_addr netmask;
  struct in_addr nexthop;

  struct in6_addr network6;
  struct in6_addr netmask6;
  struct in6_addr nexthop6;

  uint32_t metric;

  int interface;
};

// Header L2 (Ethernet)
struct ether_header {
  u_char ether_dhost[6];
  u_char ether_shost[6];
  u_short ether_type;
};

// Header L3 (IP) -- Version 4
struct iphdr {
  __u8 version : 4, ihl : 4;
  __u8 tos;
  __u16 tot_len;
  __u16 id;
  __u16 frag_off;
  __u8 ttl;
  __u8 protocol;
  __u16 check;
  __u32 saddr;
  __u32 daddr;
  /*The options start here. */
};

// Header L3 (IP) -- Version 6
struct ip6_hdr {
  union {
    struct ip6_hdrctl {
      uint32_t ip6_un1_flow; /* 4 bits version, 8 bits TC,
                                20 bits flow-ID */
      uint16_t ip6_un1_plen; /* payload length */
      uint8_t ip6_un1_nxt;   /* next header */
      uint8_t ip6_un1_hlim;  /* hop limit */
    } ip6_un1;
    uint8_t ip6_un2_vfc; /* 4 bits version, top 4 bits tclass */
  } ip6_ctlun;
  struct in6_addr ip6_src; /* source address */
  struct in6_addr ip6_dst; /* destination address */
};

// Functie care completează adresa MAC a unei interfețe (prin parametrul mac)
int get_interface_mac(int interface, uint8_t *mac);

// Functie pentru calculul checksum IP
uint16_t ip_checksum(void *vdata, size_t length);

// Adresa IPv4
struct in_addr {
  unsigned long s_addr; // load with inet_aton()
};

// Adresa IPv6
struct in6_addr {
  union {
    __u8 u6_addr8[16];
    __be16 u6_addr16[8];
    __be32 u6_addr32[4];
  } in6_u;
#define s6_addr in6_u.u6_addr8
#define s6_addr16 in6_u.u6_addr16
#define s6_addr32 in6_u.u6_addr32
};
