(define rotate-aux
  (lambda (lst pos buff)
    (cond
      ((null? lst) buff)
      ((zero? pos) (append lst buff))
      (else (rotate-aux (cdr lst) (- pos 1) (append buff (list (car lst))))))))
; 末尾に追加するの，下以外にもっといい書き方ありますか？
; (append buff (append (car lst)))

(define rotate
  (lambda (lst pos)
    (rotate-aux lst pos '())))

(print (rotate '(0 1 2 3 4 5) 3))
