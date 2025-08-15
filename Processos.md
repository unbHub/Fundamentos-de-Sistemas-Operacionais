#### Processo:
– Código executável
– Pilha de execução: contendo valores de variáveis locais
– Apontador para pilha: registrador da CPU que armazena em qual área de memória está a pilha
– Contador de programa: registrador da CPU que armazena a próxima instrução a ser executada
– Valores dos registradores gerais da máquina

#### Diferença entre um processo e um programa:
– Programa: receita de bolo (passivo)
– Processo: ato de fazer o bolo (ativo)
– Cozinheiro: CPU
– Ingredientes do bolo: dados de entrada
– Bolo: dados de saída
###### Processos envolvem uma atividade
###### Programas envolvem algoritmos
![[Pasted image 20240504163347.png]]

#### Classificação dos *modelos de processos* quanto ao custo de troca de contexto e de manutenção
###### – Heavyweight (processo tradicional) 
###### – Lightweight (threads)
- O processo é composto tanto pelo ambiente como
pela execução
- Cada processo possui um único fluxo de controle
(contador de programa) e roda de forma
independente dos demais
- Em um determinado instante, há vários processos
ativos ao mesmo tempo, o processador é chaveado
entre diversos processos.
![[Pasted image 20240504163612.png]]
- São necessários mecanismos para permitir a criação de processos
- Os processos são criados:
	– Início do sistema
	– Execução de uma chamada ao sistema de criação de
	processo por um processo em execução
	– Requisição do usuário
	– Início de um job de lote
- Quando um sistema operacional é carregado, são criados diversos processos
- Alguns executam em primeiro plano e interagem com usuários
- Outros executam em segundo plano: chamados de **daemons**
- Normalmente os processos são criados por outro

#### Término de Processos
Condições de término de processos:
– Saída normal (voluntária)
– Saída por erro (voluntária)
– Erro fatal (involuntário)
– Cancelamento por outro processo (involuntário)

#### Estado de processos
![[Pasted image 20240504164723.png]]
###### Os processos podem estar:
– Rodando
– Bloqueado
– Pronto

#### Tabela de Processos
- Cada processo tem um identificador único conhecido como **pid (process id)**

- As informações sobre um processo estão na tabela de processos (também chamada de bloco de controle de processo)

- Durante a execução, o processo compartilha o processador com outros processos em execução
	![[Pasted image 20240504165151.png]]
#### Gestão de processos
Durante a vida do sistema, processos são criados e destruídos. Essas operações
são disponibilizadas às aplicações através de chamadas de sistema; cada sistema
operacional tem suas próprias chamadas para a gestão de processos. O quadro 5.1 traz exemplos de algumas chamadas de sistema usadas na gestão de processos

![[Pasted image 20240508212403.png]]
No caso dos sistemas UNIX, a criação de novos processos é feita em duas etapas:
na primeira etapa, um processo cria uma réplica de si mesmo, usando a chamada de
sistema fork(). Todo o espaço de memória do processo inicial (pai) é copiado para o
novo processo (filho), incluindo o código da(s) tarefa(s) associada(s) e os descritores dos arquivos e demais recursos associados ao mesmo. A Figura 5.3 ilustra o funcionamento dessa chamada.
![[Pasted image 20240508212516.png]]
A chamada de sistema fork() é invocada por um processo, mas dois processos
recebem seu retorno: o processo pai, que a invocou, e o processo filho, que acabou de ser criado e que possui o mesmo estado interno que o pai (ele também está aguardando o retorno da chamada de sistema). Ambos os processos acessam os mesmos recursos do núcleo, embora executem em áreas de memória distintas.
![[Pasted image 20240508212742.png]]
A chamada de sistema exit() usada no exemplo acima serve para informar ao
núcleo do sistema operacional que o processo em questão não é mais necessário e pode ser destruído, liberando todos os recursos a ele associados (arquivos abertos, conexões de rede, áreas de memória, etc.). Processos podem solicitar ao núcleo o encerramento de outros processos, mas essa operação só é aplicável a processos do mesmo usuário, ou se o processo solicitante pertencer ao administrador do sistema.