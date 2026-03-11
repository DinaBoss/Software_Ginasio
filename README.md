# Projeto Máquina de Café - ByteCoffee

Projeto de software para máquina de café automática desenvolvido como parte da avaliação de Programação e Sistemas de Informação.

## 📋 Objetivos do Projeto

Aplicar os princípios e conceitos fundamentais da programação:
- ✅ Desenvolver programas usando linguagem C
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
├── maquina_cafe_original.c    # Versão base (módulos anteriores)
├── maquina_cafe_novo.c       # Versão atualizada (em desenvolvimento)
├── README.md                   # Documentação do projeto
└── .gitignore                 # Ficheiros ignorados
```

## 🔧 Tecnologias Utilizadas

- **Linguagem**: C
- **Compilador**: GCC/MinGW
- **Estruturas**: Arrays, Structs
- **Controlo**: if/else, while, switch
- **Modularização**: Funções especializadas

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
gcc maquina_cafe_original.c -o maquina_cafe.exe

# Executar
./maquina_cafe.exe
```

## 📝 Desenvolvimento

- **Autor**: Afonso Rosa
- **Data**: 11/03/2026
- **Versão**: 1.0 (Original) + 2.0 (Atualizada)
- **Repositório**: https://github.com/rosinhaa23/maquina-cafe-projeto

## 🔄 Commits de Desenvolvimento

1. **Commit inicial**: Programa original dos módulos anteriores
2. **Desenvolvimento**: Implementação das novas funcionalidades
3. **Refatoração**: Melhoria da estrutura e qualidade
4. **Testes**: Validação de todos os cenários
5. **Final**: Versão completa e documentada

## 🎯 Entrega

- **Formato**: Código fonte (.c)
- **Repositório**: Obrigatório no GitHub
- **Data limite**: 12 de março de 2026
- **Link**: Entrega no Classroom com URL do repositório
