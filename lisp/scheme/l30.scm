; #21

(define insert-at
  (lambda (new lst pos)
    (cond
      ((null? lst) '())
      ((eq? pos 1) (cons new lst))
      (else (cons (car lst) (insert-at new (cdr lst) (- pos 1)))))))

(print (insert-at "AHI" '(0 1 2 3 4 5) 3))
