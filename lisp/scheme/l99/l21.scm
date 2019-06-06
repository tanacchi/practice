(define (insert-at new lst pos)
  (cond
    ((null? lst) '())
    ((eq? pos 1) (cons new (cdr lst)))
    (else (cons (car lst) (insert-at new (cdr lst) (- pos 1))))))

(print (insert-at 'a '(0 1 2 3 4 5) 3))
