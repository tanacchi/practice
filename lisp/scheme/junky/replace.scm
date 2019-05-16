(define replace
  (lambda (old new lst)
    (cond
      ((null? lst) '())
      ((list? (car lst))
       (cons (replace old new (car lst))
             (replace old new (cdr lst))))
      ((eq? old (car lst)) (cons new (replace old new (cdr lst))))
      (else (cons (car lst) (replace old new (cdr lst)))))))

(print (replace 0 "AHI"  '(((1 2 3 0) 0 2) 0 ( 1 2 3) (1 2 0) 0 1 2)))
