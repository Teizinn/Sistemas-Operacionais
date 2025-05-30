versão simplificada de semáforo

faceis de usar e eficiente servem para proteção da seção crítica

é uma variavel que pode ter dois estados(livre ou ocupado)

livre: representado por 0. Se está livre o processo entra em seção crítica 
ocupado: diferente de 0. Se está ocupado fica bloqueado até que o outro processo termine e chame mutex_unlock(Chama mutex_unlock assim que termina de rodar.)

caso tenham varios processos estiverem bloquenado, será escolhido aleatoriamente.


