# Методы трансляции. ЛР №2

[![Build Status](https://travis-ci.org/z8432k/feodorov-translation-lab2.svg?branch=master)](https://travis-ci.org/z8432k/feodorov-translation-lab2)

Вариант №8

## Восходящая трансляция

LR(1) разбор

### Задание

Вынесение общего множителя за скобки

```ebnf
<S> ::= <E>
<E> ::= <E> + <T>
<E> ::= <E> - <T>
<E> ::= <T>
<T> ::= <T> * <F>
<T> ::= <F>
<F> ::= k | m | n
```
