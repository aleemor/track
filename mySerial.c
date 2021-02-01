// Alessandro Moretti

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/timeb.h>
#include <sys/time.h>
#include <stdbool.h>
#include <netdb.h>
#include <mysql/mysql.h>

// parametri database
const char* host = "localhost";                      
const char* database = "dataTrack";
const char* db_usr = "root";
const char* db_psw = "11235813213455";

float h_dop;
float lat_1;
float lon_1;
float lat_2;
float lon_2;
float lat_3;
float lon_3;

bool create_database = false;
bool drop_table_ifExists = true;
bool useCSV = true;
bool useMySQL = true;
bool createFileDat = true;

#define serial_baudrate B115200

int serial_file_descriptor, bytes_read;

//char serial_port[] = "/dev/cu.usbmodem14201";
//char serial_port[] = "/dev/cu.usbmodem14101";
//char serial_port[] = "/dev/cu.usbserial-1410";
//char serial_port[] = "/dev/ttyACM0";
char serial_port[] = "/dev/ttyUSB0";

FILE *fp;
FILE *frssi;
FILE *fsnr;
FILE *fpdr;
   
struct dati{ 
  uint8_t  preambolo;
  uint8_t  n_reboot;  
  uint8_t  batt;
  uint8_t  h_dop;
  uint16_t n_packetSent;
  uint16_t sec;
  uint16_t id;       
  uint16_t lat_1;     
  uint16_t lon_1;
  uint16_t lat_2;     
  uint16_t lon_2;
  uint16_t lat_3;     
  uint16_t lon_3;
  int16_t  rssi;
  int32_t  snr;
  float    pdr;
} pack; 

time_t seconds;
time_t start;
time_t attuale;

unsigned char read_buffer[sizeof(pack)]; 

void serial_initialize() {
	serial_file_descriptor = open(serial_port,O_RDWR );
    printf("dimensione pack: %d\n", sizeof(pack));
    if(serial_file_descriptor == -1) {
        printf("Serial port error\n");
    }
    else {
        printf("Serial port opened\n");
    }
    struct termios SerialPortSettings;
    tcgetattr(serial_file_descriptor, &SerialPortSettings);
    cfsetispeed(&SerialPortSettings,serial_baudrate);
    cfsetospeed(&SerialPortSettings,serial_baudrate);
    SerialPortSettings.c_cflag &= ~PARENB;
    SerialPortSettings.c_cflag &= ~CSTOPB;
    SerialPortSettings.c_cflag &= ~CSIZE;
    SerialPortSettings.c_cflag |=  CS8;
    SerialPortSettings.c_cflag &= ~CRTSCTS;
    SerialPortSettings.c_cflag |= CREAD | CLOCAL;
    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
    SerialPortSettings.c_iflag &= ~(  ECHO | ECHOE | ISIG);
    SerialPortSettings.c_oflag &= ~OPOST;
    SerialPortSettings.c_cc[VMIN] = sizeof(pack);
    SerialPortSettings.c_cc[VTIME] = 1;
    if((tcsetattr(serial_file_descriptor,TCSANOW,&SerialPortSettings)) != 0) {
        printf("ERROR ! in Setting attributes\n");
    }
}

void display_struct() {
    
    printf("\npreamb: ");
    printf("%d",pack.preambolo);
    printf("\nn_reboot: ");
    printf("%d",pack.n_reboot);
    printf("\nbatt: ");
    printf("%d",pack.batt);
    printf("\nh_dop: ");
    printf("%d",pack.h_dop);
    printf("\nn_packetSent: ");
    printf("%d",pack.n_packetSent);    
    printf("\nsec: ");
    printf("%d",pack.sec);
    printf("\nid: ");
    printf("%d",pack.id);
    printf("\nlat_1: ");
    printf("%d",pack.lat_1);
    printf("\nlon_1: ");
    printf("%d",pack.lon_1);
    printf("\nlat_2: ");
    printf("%d",pack.lat_2);
    printf("\nlon_2: ");
    printf("%d",pack.lon_2);
    printf("\nlat_3: ");
    printf("%d",pack.lat_3);
    printf("\nlon_3: ");
    printf("%d\n",pack.lon_3);
    printf("rssi: ");
    printf("%d\n",pack.rssi);
    printf("snr: ");
    printf("%d\n",pack.snr);    
    printf("PDR: ");
    printf("%.2f\n",pack.pdr);     
    
    printf("\n");
}

void creo_file_CSV(){
    
    if (useCSV) {
        fp = fopen("datiSeriale.csv" , "w");

        if (fp == NULL ) {
            printf("apertura fallita\n");
        }

        fprintf(fp , "unixtime;preambolo;sec;n_reboot;id;batt;h_dop;RSSI;PDR;SNR;lat_1;lon_1;lat_2;lon_2;lat_3;lon_3\n");

        fclose(fp);
    }

}

void creo_file_dat(){
    
    if(createFileDat){
    
        frssi = fopen("rssi.dat" , "w");

        if (frssi == NULL ) {
            printf("apertura fallita\n");
        }

        fclose(frssi);
    
        fsnr = fopen("snr.dat" , "w");

        if (fsnr == NULL ) {
            printf("apertura fallita\n");
        }

        fclose(fsnr);
    
        fpdr = fopen("pdr.dat" , "w");

        if (fpdr == NULL ) {
        printf("apertura fallita\n");
        }

        fclose(fpdr);    
    }
    
}

void finish_with_error(MYSQL *con) {
    fprintf(stderr,"%s\n",mysql_error(con));
    mysql_close(con);
    exit(1);
}

void packToCSV(){
    
    if(useCSV){
    
        printf("Secondi dal 1 gennaio 1970: %ld\n",seconds);

        fp = fopen("datiSeriale.csv" , "a");

        if (fp == NULL ) {
            printf("apertura fallita\n");
        }

        fprintf(fp , "%ld;%d;%d;%d;%d;%d;%.2f;%d;%d;%.2f;" ,seconds,pack.preambolo,pack.sec,pack.n_reboot,pack.id,pack.batt,h_dop,pack.rssi,pack.snr,pack.pdr);
        fprintf(fp , "%.3f;%.3f;%.3f;%.3f;%.3f;%.3f\n",lat_1,lon_1,lat_2,lon_2,lat_3,lon_3);   
    
        fclose(fp);
    }
}

void packToDatabase(){
    
    if(useMySQL){
    
        MYSQL *con = mysql_init(NULL);
	
        if (con==NULL) {
            fprintf(stderr, "%s\n", mysql_error(con));
            exit(1);
        }
    
        if (mysql_real_connect(con, host, db_usr, db_psw, database, 0, NULL, 0)==0) {
            finish_with_error(con);
        }
    
        char buf[1024] = {};
        char query_string[]={"INSERT INTO infoTrack VALUES(%ld,%d,%d,%d,%d,%d,%.2f,%d,%d,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f)"};  
        sprintf(buf,query_string,seconds,pack.preambolo,pack.sec,pack.n_reboot,pack.id,pack.batt,h_dop,pack.rssi,pack.snr,lat_1,lon_1,lat_2,lon_2,lat_3,lon_3);
        if (mysql_query(con,buf)) {
            finish_with_error(con);
        }
    
        mysql_close(con);
    }
    
}

void scrivo_file_dat(){
    
    if(createFileDat){

        frssi = fopen("rssi.dat" , "a");

        if (frssi == NULL ) {
            printf("apertura fallita\n");
        }
    
        fprintf(frssi, "%ld %d\n",attuale,pack.rssi);
    
        fclose(frssi);  
      
        fsnr = fopen("snr.dat" , "a");

        if (fsnr == NULL ) {
            printf("apertura fallita\n");
        }
    
        fprintf(fsnr, "%ld %d\n",attuale,pack.snr);
    
        fclose(fsnr);  
    
        fpdr = fopen("pdr.dat" , "a");

        if (fpdr == NULL ) {
            printf("apertura fallita\n");
        }
    
        fprintf(fpdr, "%ld %.2f\n",attuale,pack.pdr);
    
        fclose(fpdr);   
    }   
}

void serial_listen(){
    printf("Serial listening\n");
    
    time(&seconds);
    start = seconds;

    while(true) {
        time(&seconds);
        attuale = seconds - start;
        
        bytes_read = read(serial_file_descriptor,&read_buffer,sizeof(pack));
 
        printf("Serial received: size: %d , preambolo: %d , tempo: %ld \n",  bytes_read, read_buffer[0],attuale);
        if(bytes_read == sizeof(pack) ) {
            memcpy(&pack,read_buffer,sizeof(pack));
            
            h_dop=(pack.h_dop)/10.0;
            lat_1=(pack.lat_1)/1000.0;
            lon_1=(pack.lon_1)/1000.0;
            lat_2=(pack.lat_2)/1000.0;
            lon_2=(pack.lon_2)/1000.0;
            lat_3=(pack.lat_3)/1000.0;
            lon_3=(pack.lon_3)/1000.0;
            
            display_struct();
            packToCSV();   
            packToDatabase();  
            scrivo_file_dat();
            
        }

    }
}

void mySql_initialize() {
    
    if(useMySQL){
	
        printf("mySQL client version: %s\n",mysql_get_client_info());
	
        MYSQL *con = mysql_init(NULL);
	
        if (con==NULL) {
            fprintf(stderr, "%s\n", mysql_error(con));
            exit(1);
        }
    
        if (mysql_real_connect(con, host, db_usr, db_psw, database, 0, NULL, 0)==0) {
            finish_with_error(con);
        }
    
        if (create_database) {
            mysql_query(con,"CREATE DATABASE dataTrack");
            printf("database created: dataTrack\n");
            finish_with_error(con);
        }
    
        if (drop_table_ifExists) {
            if (mysql_query(con, "DROP TABLE IF EXISTS infoTrack")){
            printf("table dropped: infoTrack\n");
            finish_with_error(con);
            }
        }
    
        mysql_query(con,"CREATE TABLE infoTrack(unixTime INT,preambolo INT,sec INT,n_reboot INT,id INT,batt INT,h_dop FLOAT(3,1),rssi INT,snr INT,lat_1 FLOAT(5,3),lon_1 FLOAT(5,3),lat_2 FLOAT(5,3),lon_2 FLOAT(5,3),lat_3 FLOAT(5,3),lon_3 FLOAT(5,3) )");            
        printf("table created: infoTrack\n");
	
        mysql_close(con);
    }
	
}

int main(void) {

    printf("Hello! \n");
    mySql_initialize();
    serial_initialize();
    creo_file_CSV();
    creo_file_dat();
    serial_listen();

    return 0;
}

