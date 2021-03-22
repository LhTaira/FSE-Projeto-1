# Projeto 1 - 2020/2

Projeto 1 da disciplina de Fundamentos de Sistemas Embarcados (2020/2)

Este trabalho faz parte da atividade proposta no seguinte repositório:
https://gitlab.com/fse_fga/projetos_2020_2/projeto-1-2020.2

## Instruções de uso

### Rodando o programa
Na pasta raiz do projeto
* Para compilar rode o comando:
`make`
<br>
* Para executar rode o comando:
`make run`

### Usando o programa

O menu inicial mostra três opções. Use as setas para cima e baixo para navegar entre elas e pressione enter par selacionar.

1. Primeira opção
O programa irá pegar a temperatura de referência pelo potenciômetro a cada um segundo e seguida será mostrada uma tela com as temperaturas TI, TE e TR que será atualizada a cada segundo.
Aperte a tecla ESC para voltar ao menu inicial

2. Segunda opção
O programa irá mostrar uma tela com um campo para o usuário colocar a temperatura de referência desejada.
Digite a temperatura desejada e aperte enter para confirmar.
Aperte a tecla ESC para voltar ao menu inicial

Observações:
* Não é possível deletar um caractere do campo de input. Para apagar o campo é nescessário apertar enter para confirmar e depois escrever novamente.
* É nessessário escrever a temperatura como ponto flutuante, ou seja, com um ponto e pelo menos uma casa decimal. Ex: `30.0`
* Se o usuário colocar uma temperatura menor que a temperatura ambiente, ele irá usar a temperatura ambiente como referência.
* Se o usuário colocar uma temperatura maior do que 100 graus celsius, o programa irá usar 100 graus como referência.

3. Opção sair
O programa fechará.
Para fechar o programa pode ser digitado ctr+c no terminal e o programa sairá normalmente.

## Parâmetros de PID

No cálculo do PID foram usadas as seguintes variáveis

- **Kp** = 5.0
- **Ki** = 1.0
- **Kd** = 35.0

## Log
Enquanto controla as temperaturas, o programa gera um histórico das temperaturas, pids e a data a cada 2 segundos.
Caso um arquivo chamado log.csv exista, o programa irá colocar o histórico no final do arquivo. Caso contrário ele irá criar o arquivo e registrar os dados no seguinte formato:
`d-m-yyyy h:m:s,TI,TE,TR,pidResistor,pidFan\n`


## Experimento
 
A aplicação foi rodada por 10 minutos na raspberry pi 1 do professor e foram obtidos os seguintes dados que estão guardados neste repositório no arquivo test-log.csv

Foi usado o seguinte software para plotar os dados:
https://chart-studio.plotly.com/create/#/

## 9. Referências

[PID - Wikipedia](https://pt.wikipedia.org/wiki/Controlador_proporcional_integral_derivativo)  
[Driver da Bosh para o sensor BME280](https://github.com/BoschSensortec/BME280_driver)  
[Biblioteca BCM2835 - GPIO](http://www.airspayce.com/mikem/bcm2835/)  
[Controle do LCD 16x2 em C](http://www.bristolwatch.com/rpi/i2clcd.htm)  
[Biblioteca WiringPi GPIO](http://wiringpi.com)  
[PWM via WiringPi](https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c)


