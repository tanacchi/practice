; #14

(define dupli
  (lambda (lst)
    (cond
      ((null? lst) '())
      (else (append (list (car lst) (car lst)) (dupli (cdr lst)))))))

(print (dupli '(0 1 2 3 4 5)))


; #15

(define make-repeat
  (lambda (elem count)
    (cond
      ((zero? count) '())
      (else (cons elem (make-repeat elem (- count  1)))))))

(define repli
  (lambda (lst count)
    (cond
      ((null? lst) '())
      (else (append (make-repeat (car lst) count) (repli (cdr lst) count))))))

(print (repli '(0 1 2 3 4 5) 3))
