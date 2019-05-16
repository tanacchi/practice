(define insertR
  (lambda (new target lat)
    (cond
      ((null? lat) 
       '())
      ((eq? (car lat) target) 
       (list target new (insertR new target (cdr lat))))
      (else (cons (car lat) (insertR new target (cdr lat)))))))

(print (insertR "AHI" 2 '(0 1 2 3 4 5 6)))


(define insertL
  (lambda (new target lat)
    (cond
      ((null? lat) 
       '())
      ((eq? (car lat) target) 
       (list new target (insertL new target (cdr lat))))
      (else (cons (car lat) (insertL new target (cdr lat)))))))

(print (insertL "AHI" 2 '(0 1 2 3 4 5 6)))

