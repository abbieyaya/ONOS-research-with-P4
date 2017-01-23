#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct form{
	char *deviceId ;
	char *flowRuleCount;
	char *id;
	char *state;
	char *bytes;
	char *packets;
	char *duration;
	char *priority;
	char *tableId;
	char *appId;
	char *payLoad;
	char *selector;
	char *treatment;
} structForm;

int main(int argc, char *argv[])
{
	if( argc < 3 ) {
		printf( "Usage: %s [rule_input_file] [rule_output.csv]\n", argv[0] );
		exit(EXIT_FAILURE);
	}

	FILE* input = fopen( argv[1], "r" );
	FILE* output = fopen( argv[2], "w" );
	fprintf( output, "deviceId,flowRuleCount,id,state,bytes,packets,duration,priority,tableId,appId,payload,selector,treatment\n" );
	structForm rule ;
	char **temp = (char**)malloc( 16*sizeof(char*) ) ; 
	char *line = NULL;
	size_t len = 0;
	int i,j ;
	while( getline( &line, &len, input) != -1 )
	{
		temp[0] = strdup( strtok( line, ",\n\0" ) );    // deviceId = ...
		temp[1] = strdup( strtok( NULL, ",\n\0" ) );    // flowcount = ...
		strtok( temp[0], "=" );
		rule.deviceId = strdup( strtok( NULL, "=\0" ) );
		strtok( temp[1], "=" );
		rule.flowRuleCount = strdup( strtok( NULL, "=\0" ) );
		for( i = 0 ; i < atoi( rule.flowRuleCount ) ; i++ )
		{
			getline( &line, &len, input );
			temp[0] = strdup( strtok( line, "," ) );
			for( j = 1 ; j < 9 ; j++ )
				temp[j] = strdup( strtok( NULL, "," ) ) ;
			temp[9] = strdup( strtok( NULL, "\0" ) );

			//for( j = 0 ; j < 10 ; j++ )
			//	printf( "%d:%s\n", j , temp[j] );
			
			strtok( temp[0], "=" ) ;
			rule.id = strdup( strtok( NULL, "\0" ) );
			strtok( temp[1], "=" );
			rule.state = strdup( strtok( NULL, "\0" ) );
			strtok( temp[2], "=" );
			rule.bytes = strdup( strtok( NULL, "\0" ) );
			strtok( temp[3], "=" );
			rule.packets = strdup( strtok( NULL, "\0" ) );
			strtok( temp[4], "=" );
			rule.duration = strdup( strtok( NULL, "\0" ) );
			strtok( temp[5], "=" );
			rule.priority = strdup( strtok( NULL, "\0" ) );
			strtok( temp[6], "=" );
			rule.tableId = strdup( strtok( NULL, "\0" ) );
			strtok( temp[7], "=" );
			rule.appId = strdup( strtok( NULL, "\0" ) );
			strtok( temp[8], "=" );
			rule.payLoad = strdup( strtok( NULL, "\0" ) );
			strtok( temp[9], "[" );
			rule.selector = strdup( strtok( NULL, "]" ) );
			strtok( NULL, "=" );
			rule.treatment = strdup( strtok( NULL, "\n\0" ) );
			fprintf( output, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\"%s\",\"%s\"\n", 
					rule.deviceId,
					rule.flowRuleCount,
					rule.id,
					rule.state,
					rule.bytes,
					rule.packets,
					rule.duration,
					rule.priority,
					rule.tableId,
					rule.appId,
					rule.payLoad,
					rule.selector,
					rule.treatment
			       );
		}


	}

	fclose( input );
	fclose( output );





}
