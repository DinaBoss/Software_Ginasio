# Projeto Máquina de Café - ByteCoffee

Projeto de software para máquina de café automática desenvolvido em C++ como parte da avaliação de Programação e Sistemas de Informação.

## 📋 Objetivos do Projeto

Aplicar os princípios e conceitos fundamentais da programação:
- ✅ Desenvolver programas usando linguagem C++
- ✅ Utilizar diferentes estruturas de controlo
- ✅ Elaborar programa recorrendo a subprogramas
- ✅ Adequar estruturas de dados aos problemas
- ✅ Implementar solução completa e funcional

## 🏗️ Especificações Funcionais

### Painel de Seleção
- [x] Obter opção do utilizador com validação de entradas inválidas
- [x] Processar pagamento cumulativo de moedas
- [x] Calcular e devolver troco corretamente
- [x] Cancelamento com devolução total
- [x] Impressão de talão de venda
- [x] Repetição indefinida do processo

### Gestão de Inventário
- [x] Modo gestão (-99) com validação PIN (1234)
- [x] Configuração de produtos (descrição, preço, stock)
- [x] Capacidade máxima de armazenamento (12 unidades)
- [x] Indicação de "ESGOTADO" quando stock = 0
- [x] Consulta de movimentos e vendas

## 📁 Estrutura do Projeto

```
maquina-cafe-projeto/
├── maquina_cafe.cpp           # Versão completa em C++
├── README.md                  # Documentação do projeto
└── .gitignore                # Ficheiros ignorados
```

## 🔧 Tecnologias Utilizadas

- **Linguagem**: C++
- **Compilador**: G++/MinGW
- **Estruturas**: Vector, Structs
- **Controlo**: if/else, while, switch
- **Modularização**: Funções especializadas
- **Bibliotecas**: iostream, string, iomanip, vector

## 📊 Critérios de Avaliação

| Critério | Pontuação | Status |
|-----------|-----------|---------|
| Funcionalidade | 50 pts | ✅ Implementado |
| Qualidade do Código | 50 pts | ✅ Implementado |
| Estrutura Lógica | 50 pts | ✅ Implementado |
| Cumprimento Requisitos | 50 pts | ✅ Implementado |
| **TOTAL** | **200 pts** | **🎯** |

## 🚀 Como Compilar e Executar

```bash
# Compilar
g++ maquina_cafe.cpp -o maquina_cafe.exe

# Executar
./maquina_cafe.exe
```

## 📝 Desenvolvimento

- **Autor**: Afonso Rosa
- **Data**: 11/03/2026
- **Versão**: 1.0 (C++ Completo)
- **Repositório**: https://github.com/rosinhaa23/maquina-cafe-projeto

## 🎯 Entrega

- **Formato**: Código fonte (.cpp)
- **Repositório**: Obrigatório no GitHub
- **Data limite**: 12 de março de 2026
- **Link**: Entrega no Classroom com URL do repositório

## 📋 Funcionalidades Implementadas

### Sistema de Vendas
- Menu dinâmico com até 10 produtos
- Validação de entradas inválidas
- Sistema de pagamento progressivo
- Cálculo automático de troco
- Cancelamento com devolução total
- Impressão opcional de talão

### Gestão de Inventário
- Configuração dinâmica de produtos
- Controlo de stock (máximo 12 unidades)
- Indicação automática de "ESGOTADO"
- Reabastecimento controlado
- Relatório detalhado de vendas
- Estatísticas finais

### Segurança e Validação
- PIN administrador (1234)
- 3 tentativas de acesso
- Validação de capacidades
- Tratamento de erros robusto

## 🏆 Diferenciais

- **C++ Moderno**: Uso de vector, string, iomanip
- **Interface Limpa**: Menu intuitivo e organizado
- **Código Modular**: Funções bem estruturadas
- **Documentação Completa**: Comentários explicativos
- **Tratamento de Erros**: Validações robustas
- **Relatórios Detalhados**: Movimentos por produto
