## Compiler

Instalando highlights para a linguagem:

O arquivo v3a.lang pode ser adicionado juntamente aos outros arquivos GTKSourceView do seu editor de texto para que este possa realcar codigos escritos na lingugem.
O comando *make install_highlight* pode ser usado para instalar o arquivo no caminho especificado em *GTK_PATH* no Makefile

Chamada do compilador:
	./[nome do programa] -[opcoes] [arquivo de entrada] [arquivo de saida]
	
	[opcoes]:
		i: escrever codigo intermediario no arquivo de saida
		
Sintaxe da linguagem:

```
/*	assim se
	faz
	um
	comentario de multiplas linhas
*/
int b <- 2
int c;

a <- 2 + 3	//tipo de a sera inferido
c <- a+b*2

if a < b do:
	print a
else if a = b do:
	print c
end

if b > 0 do:
	for i from 10 to 0 do:	//variavel de contagem nao precisa ser declarada previamente
		print i
	end
else for i stepping 2 from 0 to 20 do:	//diferente, nao?
	print i
end

while c > b do:
	print c
	c <- c-1
end

a <- 0
repeat:
	print a
	a <- a+1
until a = 10

type Person has:
	char initial
	int number
end

Person bob

bob's number <- 0
bob's initial <- 'b'

b <- bob's initial

switch a :
	case 1 do:
		print 1
	case 2 do:
		print 2
	default do:
		print a
end

int matrix m1[5][5]

for i from 0 to m1's rows do:
	for j from 0 to m1's colums do:
		m1[i][j] <- i * m1's rows + j
		print m1[i][j]
	end
end

m2d <- 4
float vector m2[m2d]	//vetor = matriz coluna

for i from 0 to m2's rows do:
	m2[i] <- i/2.0
	print m2[i]
end

int list l

for i from 0 to 4 do:
	l push back i		//adicionar i ao fim de l
	l push front i-2	//adicionar i-2 ao inicio de l
end

it <- l's first
for i from 0 to 2 do:
	it <- it's next
end

l push 10 after it	//adiciona 10 logo apos iterador
l push 6 before it	//adiciona 6 logo antes de iterador

print l pop it		//remove elemento no indice do iterador
print l pop back	//remove ultimo elemento
print l pop front	//remove primeiro elemento

it <- l's first
while it inbounds do:
	print it's content
	it <- it's next
end


```

