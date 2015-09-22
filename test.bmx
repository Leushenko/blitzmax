
Framework BRL.Blitz
SuperStrict

Function Foo:Int(x:Int)
	Local y:Int = x * 2
	Return x + y + 1
End Function

'?C
Function Bar:Int(y:Int)
	Local z:Int = y + 3
	Return Foo(z)
End Function
?

Global C:Int = 65, D:Long = 650000000000:Long, E:Double = 19.6:Double, F:Float = 23.4, G:Float() = Baz.A

Type Baz
	Field msg:String
	Method M()
		msg = "in m"
	End Method
	
	Function A:Float()
		Return 5.5
	End Function
	Function B:Long(d:Double, l:Long)
		Return 5:Long
	End Function
	
	Global X:Float = Baz.A()
End Type

'Print "done."
End

Private
Global A:Int = 49
Function B:Float()
	Return 5.5
End Function
Public
