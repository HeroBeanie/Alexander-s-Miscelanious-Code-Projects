#include<stdio.h>
  int sel=0;
  double classes;
  double cpi;
  double total;
  double speed;
  double count;
  double  sum;
  double  avg;
  double time;
  double  mips;
  int acount[20];
  int acpi[20];
main(void){
  Selection();
  return;
}
int Calculations(){
  classes=0;
  cpi=0;
  total=0;
  speed=0;
  count=0;
  sum=0;
  avg=0;
  time=0;
  mips=0;
  int a;

  printf("Please Enter Number of Instruction Classes:");
  scanf("%lf",&classes);
  printf("\n\n");
  printf("Please Enter the Frequency(MHz):");
  scanf("%lf",&speed);
  printf("\n\n");
  for(a=0;a<classes;a++){
    printf("Please Enter CPI of Class ");
    printf("%d",a+1);
    printf(":");
    scanf("%lf",&cpi);
    acpi[a]=(int)cpi;
    printf("\n");
    printf("Please Enter the Instruction Count of Class ");
    printf("%d",a+1);
    printf("(million):");
    scanf("%lf",&count);
    acount[a]=(int)count;
    printf("\n\n");
    total = total+count;
    sum = (cpi * count)+sum;
  }
  avg = sum/total;
  time = ((total*avg)/speed);
  mips = total/time;
  Selection();
}
int Print(){
  int b;
  printf("FREQUENCY(MHz):");
  printf("%.2f",speed);
  printf("\n\n");
  printf("INSTRUCTION DISTRIBUTION\n\n");
  printf("CLASS   CPI  COUNT \n");
  for(b=0;b<classes;b++){
    printf("%d",b+1);
    printf("        ");
    printf("%d",acpi[b]);
    printf("        ");
    printf("%d",acount[b]);
    printf("\n\n");
  }
  printf("PERFORMANCE VALUES\n\n");
  printf("Avg = %.2f\n ", avg);
  printf("Time = %.2f\n ",time*1000);
  printf("MIPS =%.2f\n ",mips);
  printf("\n");
  Selection();
}
int Selection(){
  sel=0;
  printf("Alexander Cloutier-Nosik\n");
  printf("Performance Assesment\n\n");
  printf("--------------------\n\n");
  printf(" 1) Enter Parameters\n");
  printf(" 2) Print Results\n");
  printf(" 3) Quit\n\n");
  printf("Enter Selection:");
  scanf("%d",&sel);
  printf("\n");
  if(sel==1){
    Calculations();
  }
  else if(sel==2){
    Print();
  }
  else if(sel==3){
    printf("Program has Terminated Normally\n");
  }
else{
    printf("Please Choose a Valid Selection");
    Selection();
  }
  return;

}

