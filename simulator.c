#include<stdio.h>
#include<stdint.h>

#define SIZE 256//1 kByte  



uint32_t R[32];
uint32_t ram[SIZE];
uint32_t opcode, rs, rt, rd, shamt, funct;
uint32_t pc = 0, ic = 0;



int main (int argc, char *argv[]) {
	uint32_t *ptr;
      	
	FILE *arq;	
	int result;
	
	// Abre um arquivo BINÁRIO para LEITURA
	arq = fopen(argv[1], "r+b");

	if (arq == NULL){  // Se houve erro na abertura
		printf("Problemas na abertura do arquivo\n");
		return 0;
	}

	result = fread (ram, 4,100, arq);   // (buffer, numero de bytes, qnde de dados que vai tentar ler, arquivo)
	printf("Nro de elementos lidos: %d\n", result);

	int i;		

	for (i=0; i < result; i++){
		printf("%01x \n", (unsigned int) ram[i]);
		uint32_t instruct;

		for(i = 0; i < result; i++){
			pc = i;	
			ic = (uint32_t)ram[pc];

			instruct = ((ic & 0xFF000000) >> 24 | (ic & 0x00FF0000) >> 8 | (ic & 0x0000FF00) << 8 |  (ic & 0x000000FF) << 24 );     
			
			ic = instruct;
												   										       
			opcode = (ic & 0xFC000000) >> 26;          //separando os operadores do opcode
			rs = (ic & 0x3E00000) >> 21;
			rt = (ic & 0x1F0000) >> 16;
			rd = (ic & 0xF800) >> 11;
			shamt = (ic & 0x7C0) >> 6;
			funct = (ic & 0x3F);

			printf("\n opcode %01x | rs %01x | rt %01x | rd %01x | shamt %01x | funct %01x\n", opcode, rs, rt, rd, shamt, funct);//printf("%01x ", instruct);
			
			R[rs] = 10;
			R[rt] = 5;			

			switch(opcode){
				case 0x00:
					switch(funct){//TIPO R
                        case 0x00:
                            R[rd] = (R[rs] >> R[shamt]);
							printf("  SLL: registrador destino  %d\n\n", R[rd]);	
						    break;
                        
                        case 0x02:
                            R[rd] = (R[rs] << R[shamt]);
							printf("  SRL: registrador destino  %d\n\n", R[rd]);	
						    break;

                        case 0x03://?
                            R[rd] = (R[rs] - R[shamt]);
							printf("  SRA: registrador destino  %d\n\n", R[rd]);	
						    break;

						case 0x20:
							R[rd] = R[rs] + R[rt];
							printf("  ADD: registrador destino  %d\n\n", R[rd]);	
						    break;

						case 0x22:
							R[rd] = R[rs] - R[rt];
							printf("  SUB: registrador destino  %d\n\n", R[rd]);	
						    break;
                        
                        case 0x24:
                            R[rd] = (R[rs] && R[rt]);
							printf("  AND: registrador destino  %d\n\n", R[rd]);	
						    break;

                        case 0x25:
                            R[rd] = (R[rs] || R[rt]);
							printf("  OR: registrador destino  %d\n\n", R[rd]);	
						    break;
                        
                        case 0x26:
                            R[rd] = (R[rs] ^ R[rt]);
							printf("  XOR: registrador destino  %d\n\n", R[rd]);	
						    break;
                        
                        case 0x27:
                            R[rd] = !(R[rs] || R[rt]);
							printf("  NOR: registrador destino  %d\n\n", R[rd]);	
						    break;
                        
                        case 0x2a://?
                            R[rd] = (R[rs] || R[rt]);
							printf("  SLT: registrador destino  %d\n\n", R[rd]);	
						    break;
					}//switchfunct
			}//switchopcode			
		}//for
    }//for
	return 0;
}//main