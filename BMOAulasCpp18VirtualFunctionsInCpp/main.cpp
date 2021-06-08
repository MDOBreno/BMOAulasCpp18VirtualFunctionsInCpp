//
//  main.cpp
//  BMOAulasCpp18VirtualFunctionsInCpp
//
//  Created by Breno Medeiros on 08/06/21.
//

#include <iostream>
#include <string>

class Entidade {
public:
    
    std::string GetNome() {
        return "Entidade";
    }
    //A diferença entre o metodo de cima e o de baixo é que a de baixo é virtualizada, permitindo q o metodo sobrescrito de mais baixa
    // hierarquia seja o chamado automaticamente(ou seja, sem termos que ficar checando individualmente o tipo de uma instancia para
    // poder escolher qual das classes da herança deve ter conter o metodo que será usado). Se nao entendeu ficara mais claro no fim da main()
    virtual std::string GetNomeVirtualizado() {
        return "Entidade";
    }
};

class Jogador:public Entidade {
private:
    std::string m_Nome;
public:
    Jogador(const std::string& nome):m_Nome(nome) { //Essa linha denota "o argumento 'nome' sera armazenado no atributo m_Nome"
        
    }
    
    std::string GetNome() {
        return m_Nome;
    }
    //Repare(faça o teste) que na linha abaixo: mesmo removendo o 'override' ainda funcionara, mas mesmo assim é uma boa pratica escrever pois:
    // 1) Quem ler esse codigo saibera que o metodo da classe pai é Virtual. 2) Ajuda a resolver bugs durante a criacao da mesma, visto que
    // o compilador alertara o desenvolvedor caso 'o metodo que voce escreve nao tem exatamente o mesmo nome que o metodo pai', ou se por exemplo
    // 'o metodo da classe pai nao esta escrito como 'virtual'.
    std::string GetNomeVirtualizado() override {
        return m_Nome;
    }
    
};

void PrintNome(Entidade* entidade) { //O argumento que for passado para este metodo sera interpretado como a classe 'Entidade'
    std::cout << entidade->GetNome() << "\n" << std::endl;
}

void PrintNomeVirtualizado(Entidade* entidade) { //O argumento que for passado para este metodo sera interpretado como a classe 'Entidade'
    std::cout << entidade->GetNomeVirtualizado() << "\n" << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Entidade* e = new Entidade();
    //Abaixo, repare que o tipo de 'e' é 'Entidade *'(um ponteiro), entao para chamar o metodo de quem 'e' aponta usamos a seta '->'
    std::cout << e->GetNome() << "\n" << std::endl;
    
    Jogador* j = new Jogador("Breno");
    std::cout << j->GetNome() << "\n" << std::endl;
    
    std::cout << " ---------------------- Casos Especificos ----------------------\n";
    
    Entidade* entidadeInstanciadaComoJogador = j;
    std::cout << entidadeInstanciadaComoJogador->GetNome() << "\n" << std::endl; //Resultado: Tudo o que pertence apenas a Jogador se perde.
    //De forma semelhante, se passarmos 'e' e 'j' para um metodo que esta recebendo argumentos como 'Entidade', isso é o que ocorre:
    PrintNome(e);
    PrintNome(j);
    
    std::cout << " ----- Resolvendo os problemas acima com Funcao Virtual --------\n";
    
    //Para evitar que o que ocorreu acima aconteca, existe uma coisa chamada 'Vtable', que basicamente consiste de definir como virtual
    // o metodo em sobrescrita/overide (nesse caso "GetNome()") na classe paiDeTodos(Ou seja, a classe que esta acima de todo como 'pai,neto..',
    // e nesse caso é Entidade).
    PrintNomeVirtualizado(e);
    PrintNomeVirtualizado(j);
    //Vale lembrar que usar Funcoes Virtual geram dois custos computacionais em TempoDeExecucao/RunTime:
    //1) Armazenar(consumir) na memoria a 'Vtable'
    //2) Custo de performance, pois toda vez que esse metodo for chamado havara o trabalho de ir na tabela consultar qual metodo sera chamado
    //Para o Chermo isso nunca fez diferenca para ele em termos de custo computacional, e ele usa o tempo todo.
    
    
    return 0;
}
