#include <glade/glade.h>
#include <gtk/gtk.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void on_delete_event (GtkWidget *widget,GdkEvent* event,gpointer data); 
void on_number_clicked(GtkWidget *button,gpointer userdata);
void on_AC_clicked(GtkWidget *button,gpointer userdata);
void on_equ_clicked(GtkWidget *button,gpointer userdata);
void on_add_clicked(GtkWidget *button,gpointer userdata);
void on_sub_clicked(GtkWidget *button,gpointer userdata);
void on_mul_clicked(GtkWidget *button,gpointer userdata);
void on_div_clicked(GtkWidget *button,gpointer userdata);
GtkWidget	*label[6];
GtkWidget       *numberbutton[11];
int sign = 0;int num=0;
int main(int argc ,char * argv[])
{
	GtkBuilder      *builder;
	GtkWidget       *window;
	GtkWidget	*exitbutton;
	GtkWidget	*ACbutton;
	GtkWidget	*equbutton;
	GtkWidget	*addbutton;
	GtkWidget	*subbutton;
	GtkWidget	*mulbutton;
	GtkWidget	*divbutton;
	int i;
	gtk_init (&argc, &argv);
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "window1.glade", NULL);
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
	exitbutton = GTK_WIDGET (gtk_builder_get_object (builder, "exit"));
	ACbutton = GTK_WIDGET (gtk_builder_get_object (builder, "AC"));
	equbutton = GTK_WIDGET (gtk_builder_get_object (builder, "equ"));
	addbutton = GTK_WIDGET (gtk_builder_get_object (builder, "add"));
	subbutton = GTK_WIDGET (gtk_builder_get_object (builder, "sub"));
	mulbutton = GTK_WIDGET (gtk_builder_get_object (builder, "mul"));
	divbutton = GTK_WIDGET (gtk_builder_get_object (builder, "div"));
	for(i=0;i<=9;i++)
	{
		char number[10] = "number";
		char id[10]="0";
		id[0]=i+48;
		strcat(number,id);
		numberbutton[i] = GTK_WIDGET (gtk_builder_get_object (builder,number));
		num = i;
	g_signal_connect(G_OBJECT(numberbutton[i]),"clicked",G_CALLBACK(on_number_clicked),(gpointer)num);
	}
	for(i=0;i<=5;i++)
	{
		char _label[10] = "label";
		char id[10]="0";
		id[0]=i+48;
		strcat(_label,id);
		label[i] = GTK_WIDGET (gtk_builder_get_object (builder,_label));
	}
	gtk_builder_connect_signals (builder, NULL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(on_delete_event),NULL); 
	g_signal_connect(G_OBJECT(exitbutton),"clicked",G_CALLBACK(on_delete_event),NULL);
	g_signal_connect(G_OBJECT(ACbutton),"clicked",G_CALLBACK(on_AC_clicked),NULL);
	g_signal_connect(G_OBJECT(equbutton),"clicked",G_CALLBACK(on_equ_clicked),NULL);
	g_signal_connect(G_OBJECT(addbutton),"clicked",G_CALLBACK(on_add_clicked),NULL);
	g_signal_connect(G_OBJECT(subbutton),"clicked",G_CALLBACK(on_sub_clicked),NULL);
	g_signal_connect(G_OBJECT(mulbutton),"clicked",G_CALLBACK(on_mul_clicked),NULL);
	g_signal_connect(G_OBJECT(divbutton),"clicked",G_CALLBACK(on_div_clicked),NULL);
	g_object_unref (G_OBJECT (builder));
	gtk_widget_show_all(window);                
	gtk_main ();
	return 0;
}
void on_delete_event (GtkWidget *widget,GdkEvent* event,gpointer data) 
{
	gtk_main_quit(); 
}
void on_number_clicked(GtkWidget *button,gpointer userdata)
{
	int n = (int)userdata;
	const char *first = gtk_label_get_text(GTK_LABEL(label[0]));
	const char* second = gtk_label_get_text(GTK_LABEL(label[2]));
	char this[20]={0};
	if(sign==0)
	{sprintf(this,"%s",first);}
	else if(sign==1)
	{sprintf(this,"%s",second);}
	this[strlen(this)]='\0';
	char nthis[5];
	sprintf(nthis,"%d",n);
	strcat(this,nthis);
	if(sign==0)
	{gtk_label_set_text(GTK_LABEL(label[0]),this);}
	else if(sign ==1)
	{gtk_label_set_text(GTK_LABEL(label[2]),this);}
}
void on_AC_clicked(GtkWidget *button,gpointer userdata)
{
	char buf[10]="0";
	int i;
	for(i=0;i<=4;i++)
	{
		if(i!=3)
		{
			gtk_label_set_text(GTK_LABEL(label[i]),buf);
		}
	}
	sign = 0;
}
void on_add_clicked(GtkWidget *button,gpointer userdata)
{
	char op[10]="+";
	gtk_label_set_text(GTK_LABEL(label[1]),op);
	sign = 1;
}
void on_sub_clicked(GtkWidget *button,gpointer userdata)
{
	char op[10]="-";
	gtk_label_set_text(GTK_LABEL(label[1]),op);
	sign = 1;
}
void on_mul_clicked(GtkWidget *button,gpointer userdata)
{
	char op[10]="x";
	gtk_label_set_text(GTK_LABEL(label[1]),op);
	sign = 1;
}
void on_div_clicked(GtkWidget *button,gpointer userdata)
{
	char op[10]="/";
	gtk_label_set_text(GTK_LABEL(label[1]),op);
	sign = 1;
}
void on_equ_clicked(GtkWidget *button,gpointer userdata)
{
	const char* first = gtk_label_get_text(GTK_LABEL(label[0]));
	const char* op = gtk_label_get_text(GTK_LABEL(label[1]));
	const char* second = gtk_label_get_text(GTK_LABEL(label[2]));
	int nfirst = atoi(first);
	int nsecond = atoi(second);
	int result=0;
	if(op[0]=='+')
	{
		result = nfirst+nsecond;
	}
	else if(op[0]=='-')
	{
		result = nfirst-nsecond;
	}
	else if(op[0]=='x')
	{
		result = nfirst*nsecond;
	}
	else if(op[0]=='/')
	{
		if(nsecond==0)
		{
			char tip[50] = "second number should not be zero!";
			printf("%s\n",tip);
			gtk_label_set_text(GTK_LABEL(label[4]),tip);
		}
		result = nfirst/nsecond;
	}
	char strresult[10];
	sprintf(strresult,"%d",result);
	gtk_label_set_text(GTK_LABEL(label[4]),strresult);
	sign = 0;
}
