//by VALENTINX110 https://twitter.com/VALENTINX110    https://github.com/VALENTINX110
#include<iostream>
#include<fstream>
#include<string.h> //ik i'm using c string functions and idc
#define elsif else if
using namespace std;
float color_matrix[3][10]={0},dust_size,color_transition[3],timp, timpp; 
int matrix_column_max=0,particle_ID=1,count;
char function_name[44],function_path[501],sbobj_name[33],sbobj_value[101],execution_parameters[501],coords[201],hex_value[8],delta[101],speed[101],render[6],viewer[101];
bool loop,enable;
float put (float x,float y) {
	if (y==0) return 1;
	else for (int i=1;i<y;i++) x*=x;
	return x;
} //power function
float round(float var) {
    float value = (int)(var * 1000 + .5);
    return (float)value / 1000;
}
void ctd (char input[8], float v[3]) {
	char c[3]={'\n'};
	int i1,i2=0,j=0;
	float nr=0;
	if (input[0]=='#') strcpy(input,input+1);
	while (strlen(input)>0) {
		strncpy(c,input,2);
		nr=0; j=0;
		for(i1=1;i1>=0;i1--) {
			if ((c[i1]>='A')&&(c[i1]<='F'))nr+=(c[i1]-55)*put(16,j);
			elsif ((c[i1]>='a')&&(c[i1]<='f'))nr+=(c[i1]-87)*put(16,j);
			elsif ((c[i1]>='0')&&(c[i1]<='9')) nr+=(c[i1]-48)*put(16,j);
			j++;
		}
		v[i2]=round(nr/255); i2++;
		strcpy(input,input+2); 
	}
} //converts hex values to decimal values ranging from 0 to 1 (1st row - red values; 2nd row - green values; 3rd row - blue values.)

    
int main() {
	
	// (I) data input section
	
	cout<<"- F A D L E S -"<<'\n';
	cout<<"      > a nice little script for generating smooth transitioning colorful particles"<<'\n';
	cout<<"      > by VALENTINX110"<<'\n'<<'\n';
	cout<<"-> Enter the name of the function that will contain the particle commands (max 32 characters): ";
	cin>>function_name; cout<<'\n'<<'\n';
	cout<<"-> Enter the function path (max 500 characters): ";
	cin>>function_path; cout<<'\n'<<'\n';
	cout<<"-> Ender the name of the scoreboard objective for the frames (max 32 characters): ";
	cin>>sbobj_name; cout<<'\n'<<'\n';
	cout<<"-> Enter the fake player/selector for setting it's score on the scoreboard objective (max 100 characters): ";
	cin>>sbobj_value; cout<<'\n'<<'\n'; cin.ignore();
	cout<<"-> Enter the execution paramaters and conditions (max 500 chars): ";
	cin.get(execution_parameters,501); cin.ignore(); cout<<'\n'<<'\n';
	cout<<"-> Select the particle type by entering it's corresponding number: "<<'\n'<<"   1) dust"<<'\n'<<"   2) dust_color_transition"<<'\n'<<"   3) entity_effect"<<'\n'<<"   4) ambient_entity_effect"<<'\n';
	cin>>particle_ID; while ((particle_ID<1)||(particle_ID>4)){ cout<<'\n'<<" ! Invalid particle ID! Please select a number from 1-4: "; cin>>particle_ID; cout<<'\n';}
	cout<<'\n'; cin.ignore();
	cout<<"-> Enter the position where the particles will be created (max 100 chars): ";
	cin.get(coords,101); cin.ignore(); cout<<'\n'<<'\n';
	cout<<"-> Enter the hex color codes in the preffered order of transitions: (press enter after each hex code and type \">end\" when done - the max amount of color values is 10): ";
	enable=1;
	while (matrix_column_max<=10&&enable==1) {
		cin>>hex_value;
		if (strcmp(hex_value,">end")!=0){ ctd(hex_value,color_transition); color_matrix[0][matrix_column_max]=color_transition[0]; color_matrix[1][matrix_column_max]=color_transition[1]; color_matrix[2][matrix_column_max]=color_transition[2]; matrix_column_max++; }
		else {
			if (matrix_column_max<1) cout<<" ! Not enough values entered! You must include at least 2 values!"<<'\n';
			else enable=0;
		}
	}
	enable=0;
	cout<<'\n'<<'\n';
	cout<<"-> Enter the the time between color transtions in seconds (if a float number is entered, only 1 decimal point is allowed): ";
	cin>>timp; cout<<'\n'<<'\n';
	switch (particle_ID){
		case 1:
			cout<<"-> Enter dust size: ";
			cin>>dust_size; cout<<'\n'<<'\n'; cin.ignore();
			cout<<"-> Enter delta/motion values (max 100 characters): ";
			cin.get(delta,101); cin.ignore(); cout<<'\n'<<'\n';
			cout<<"-> Enter the speed (max 100 characters): ";
			cin>>speed; cout<<'\n'<<'\n';
			cout<<"-> Enter the count of the particles: ";
			cin>>count; cout<<'\n'<<'\n';
			break;
		case 2:
			cout<<"-> Enter the hex color code for the color transition: ";
			cin>>hex_value; ctd(hex_value, color_transition);
			cout<<"-> Enter dust size: ";
			cin>>dust_size; cout<<'\n'<<'\n'; cin.ignore();
			cout<<"-> Enter delta/motion values (max 100 characters): ";
			cin.get(delta,101); cin.ignore(); cout<<'\n'<<'\n';
			cout<<"-> Enter the speed (max 100 characters): ";
			cin>>speed; cout<<'\n'<<'\n';
			cout<<"-> Enter the count of the particles: ";
			cin>>count; cout<<'\n'<<'\n';
			break;
		case 3: 
			cout<<"-> Enter the speed (max 100 characters): ";
			cin>>speed; cout<<'\n'<<'\n';
			cout<<"-> Enter the count of the particles: ";
			cin>>count; cout<<'\n'<<'\n';
			break;
		case 4: 
			cout<<"-> Enter the speed (max 100 characters): ";
			cin>>speed; cout<<'\n'<<'\n';
			cout<<"-> Enter the count of the particles: ";
			cin>>count; cout<<'\n'<<'\n';
			break;
	}
	cout<<"-> Force/Normal: ";
	cin>>render; cout<<'\n'<<'\n';
	cout<<"-> Enter the selector for who can see the particles (max 100 characters; type \">blank\" for keeping it blank): ";
	cin>>viewer; cout<<'\n'<<'\n';
	cout<<"-> Loop mode (1 = true, 0 = false): ";
	cin>>loop; cout<<'\n'<<'\n';
	
	// (II) Generating
	cout<<"-> Generating..."<<'\n'<<'\n';

	//setting the name of the function
	strcat (function_name,".mcfunction");
	ofstream g(function_name);
	ofstream tick_outfile("fadles_tick.mcfunction");
	ofstream load_outfile("fadles_load.mcfunction");
	//generationg fadless
	float rvalue1, gvalue1, bvalue1, rvalue2, gvalue2, bvalue2, rration, gration, bration;
	int tick=0, column=0, rlogic_type=0, glogic_type=0, blogic_type=0, tick_time;
	rvalue1=color_matrix[0][column]; gvalue1=color_matrix[1][column]; bvalue1=color_matrix[2][column];
	column++;
	timpp = timp*20;
	while (column < matrix_column_max) {
		rvalue2=color_matrix[0][column]; gvalue2=color_matrix[1][column]; bvalue2=color_matrix[2][column];
		tick_time=1;
		rration = round((rvalue1-rvalue2)/timpp);
		gration = round((gvalue1-gvalue2)/timpp);
		bration = round((bvalue1-bvalue2)/timpp);
		if (rration <0) rration *=-1;
		if (gration <0) gration *=-1;
		if (bration <0) bration *=-1;

		if (rvalue1<rvalue2) rlogic_type = 1;
		else rlogic_type = 2;
		if (gvalue1<gvalue2) glogic_type = 1;
		else glogic_type = 2;
		if (bvalue1<bvalue2) blogic_type = 1;
		else blogic_type = 2;

		do {
			//inserts the fadles in the file
			switch (particle_ID) {
				case 1:
					if (strcmp(viewer,">blank")==0) g<<"execute if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run "<<"particle dust "<<rvalue1<<' '<<gvalue1<<' '<<bvalue1<<' '<<dust_size<<' '<<coords<<' '<<delta<<' '<<speed<<' '<<count<<' '<<render<<' '<<'\n';
					else g<<"execute if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run "<<"particle dust "<<rvalue1<<' '<<gvalue1<<' '<<bvalue1<<' '<<dust_size<<' '<<coords<<' '<<delta<<' '<<speed<<' '<<count<<' '<<render<<' '<<viewer<<'\n';
					break;
				case 2:
					if (strcmp(viewer,">blank")==0) g<<"execute if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run "<<"particle dust_color_transition "<<rvalue1<<' '<<gvalue1<<' '<<bvalue1<<' '<<dust_size<<' '<<color_transition[0]<<' '<<color_transition[1]<<' '<<color_transition[2]<<' '<<coords<<' '<<delta<<' '<<speed<<' '<<count<<' '<<render<<' '<<'\n';
					else g<<"execute if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run "<<"particle dust_color_transition "<<rvalue1<<' '<<gvalue1<<' '<<bvalue1<<' '<<dust_size<<' '<<color_transition[0]<<' '<<color_transition[1]<<' '<<color_transition[2]<<' '<<coords<<' '<<delta<<' '<<speed<<' '<<count<<' '<<render<<' '<<viewer<<'\n';
					break;
				case 3:
					if (strcmp(viewer,">blank")==0) g<<"execute if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run "<<"particle entity_effect "<<coords<<' '<<rvalue1<<' '<<gvalue1<<' '<<bvalue1<<' '<<speed<<' '<<count<<' '<<render<<' '<<'\n';
					else g<<"execute if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run "<<"particle entity_effect "<<coords<<' '<<rvalue1<<' '<<gvalue1<<' '<<bvalue1<<' '<<speed<<' '<<count<<' '<<render<<' '<<viewer<<'\n';
					break;
				case 4:
					if (strcmp(viewer,">blank")==0) g<<"execute if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run "<<"particle ambient_entity_effect "<<coords<<' '<<rvalue1<<' '<<gvalue1<<' '<<bvalue1<<' '<<speed<<' '<<count<<' '<<render<<'\n';
					else g<<"execute if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run "<<"particle ambient_entity_effect "<<coords<<' '<<rvalue1<<' '<<gvalue1<<' '<<bvalue1<<' '<<speed<<' '<<count<<' '<<render<<' '<<viewer<<'\n';
					break;
			}

			//setting a new transition keyframe and check weather the first value surpassed the second one
			if (rlogic_type==1) {
				if (rvalue1<rvalue2 && (round(rvalue1+rration)<rvalue2) && (tick_time < timpp)) rvalue1=round(rvalue1+rration);
				else rvalue1=rvalue2;
			}
			elsif (rlogic_type==2) {
				if (rvalue1>rvalue2 && (round(rvalue1-rration)>rvalue2) && (tick_time < timpp)) rvalue1=round(rvalue1-rration);
				else rvalue1=rvalue2;
			}
			if (glogic_type==1) {
				if (gvalue1<gvalue2 && (round(gvalue1+gration)<gvalue2) && (tick_time < timpp)) gvalue1=round(gvalue1+gration);
				else gvalue1=gvalue2;
			}
			elsif (glogic_type==2) {
				if (gvalue1>gvalue2 && (round(gvalue1+gration)>gvalue2) && (tick_time < timpp)) gvalue1=round(gvalue1-gration);
				else gvalue1=gvalue2;
			}
			if (blogic_type==1) {
				if (bvalue1<bvalue2 && (round(bvalue1+bration)<bvalue2) && (tick_time < timpp)) bvalue1=round(bvalue1+bration);
				else bvalue1=bvalue2;
			}
			elsif (blogic_type==2) {
				if (bvalue1>bvalue2 && (round(bvalue1-bration)>bvalue2) && (tick_time < timpp)) bvalue1=round(bvalue1-bration);
				else bvalue1=bvalue2;
			}
			tick++; tick_time++;
		}while ((rvalue1 != rvalue2) || (gvalue1 != gvalue2) || (bvalue1 != bvalue2));
		g<<'\n';
		column++;
	}
	cout<<" - D O N E - "<<'\n'<<'\n';

	cout<<"-> The commands required to put in the repeating function is in the \"fadles_tick.mcfunction\" file!"<<'\n'; 
	tick_outfile<<"execute "<<execution_parameters<<' '<<"if score "<<sbobj_value<<' '<<sbobj_name<<" matches 0.."<<tick<<" run scoreboard players add "<<sbobj_value<<' '<<sbobj_name<<" 1"<<'\n';
	if (loop==1) tick_outfile<<"execute "<<execution_parameters<<' '<<"if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run scoreboard players set "<<sbobj_value<<' '<<sbobj_name<<" 0"<<'\n';
	if (loop==0) tick_outfile<<"execute "<<execution_parameters<<' '<<"if score "<<sbobj_value<<' '<<sbobj_name<<" matches "<<tick<<" run scoreboard players reset "<<sbobj_value<<' '<<sbobj_name<<'\n';
	tick_outfile<<"execute "<<execution_parameters<<' '<<"if score "<<sbobj_value<<' '<<sbobj_name<<" matches 0.."<<tick<<" run function "<<function_path<<'\n';
	
	cout<<"-> The commands required to put in the load function is in the \"fadles_load.mcfunction\" file!"; 
	load_outfile<<"scoreboard objectives add "<<sbobj_name<<" dummy"<<'\n';
	load_outfile<<"tellraw @a {\"text\":\"<FADLES> Enjoy the colorful show! :)\",\"color\":\"green\"}"<<'\n';
	load_outfile<<"execute as @a at @s run playsound minecraft:block.note_block.banjo master @s ~ ~ ~ 1 1";
	return 0;
}
//old code from the ancient times of 2021 that generated a nice rainbow fade for me
/*  float x=255,y,z;
	int k=3,r,c;
	cout<<"Ration: "; cin>>r;
	while (k>0) {
		g<<"execute at @e[type=item,nbt={tag:{funbow:1b}},scores={rainbowFade="<<c<<"}] run "<<"particle dust "<<x/255<<' '<<y/255<<' '<<z/255<<" 1 ~ ~0.3 ~ 0.3 0.3 0.3 0.01 1 force"<<endl;
		if (k==3) {
			if (y<255) y+=r; elsif (x>0) x-=r;
			if (x==0&&y==255) k--;
		}
		if (k==2) {
			if (z<255) z+=r; elsif (y>0) y-=r;
			if (y==0&&z==255) k--;
		}
		if (k==1) {
			if (x<255) x+=r; elsif (z>0) z-=r ;
			if (z==0&&x==255) k--;
		}
		c++;
	}
	cout<<"DONE!";
	cout<<" Max scoreboard time is "<<c;*/
