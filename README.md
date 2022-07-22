# Projeto Camarão App - IoT :shrimp:

![image](https://user-images.githubusercontent.com/48811215/180436128-30fc9886-fa38-4e0c-bc10-678ef5452f20.png)
![image](https://user-images.githubusercontent.com/48811215/180436016-f2187fd9-387d-46bf-9bfd-3576f9fc15ca.png)

Este foi um projeto feito para uma Iniciação Científica na UFRPE.

Com a necessidade de produção de camarões em escala e com qualidade, após pesquisas, descobriu-se que os camarões se desenvolvem melhor quando mantidos em temperaturas
entre 25 e 28ºC.
https://www.engepesca.com.br/post/carcinicultura-fatores-indispensaveis-para-o-sucesso-do-negocio


Dada esta informação, surgiu com a orientação do Professor Obionor Nóbrega, a ideia de construção de um sistema para monitoramento da temperatura da água em tempo real para camarões criados em cativeiro (Carcinicultura).

Com meus conhecimentos de hardware e programação, criei esta solução e a chamei de Camarão App.



**O que faz?**

A solução monitora  a temperatura da água em tempo real, caso a temperatura ultrapasse o pré-configurado pelo usuário, um alerta é emitido tanto no hardware (Luminoso e sonoro) quanto no software (Luminoso e gráfico).


**Como funciona?**
A solução inicializa com um limiar máximo  e mínimo de temperatura e inicia o monitoramento em ºC. 

O usuário também pode ajustar os limiares no através do software *Blynk* no celular e confirmar as temperaturas desejadas. E verificar o gráfico plotado em tempo real e a temperatura ºC.


**Quais foram as tecnologias utilizadas no projeto?**

**Hardware:**

Protoboard, NodeMCU, Potenciômetro 10K, Display LCD, Led RGB, Buzzer, Sensor de temperatura, borne, jumpers e um cabo de alimentação USB.

**Software:**

Arduino IDE (Linguagem C), Blynk App *(Servidor)* e Blynk App *(Aplicativo android)*.
https://www.arduino.cc

https://blynk.io


**Quanto custou?**
Cerca de R$150,00


**Quanto tempo levei para concluir o protótipo?**
15 dias



author: @davidcarvalhou
