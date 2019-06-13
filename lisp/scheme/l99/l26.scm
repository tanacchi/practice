(define (combination num lst)
  (define (combination-aux num lst result)
    (cond
      ((zero? num) (list result))
      ((null? lst) '())
      (else (append (combination-aux (- num 1) (cdr lst) (cons (car lst) result))
                    (combination-aux num (cdr lst) result)))))
  (combination-aux num lst '()))

(display (length (combination 4 '(0 1 2 3 4 5 6 7 8))))
